using System;
using System.Collections.Generic;
using System.IO;
using Antlr4.Runtime;
using Antlr4.Runtime.Tree;
using UScript.Compiler.AST;
using UScript.Compiler.AST.Visitor.V1;
using UScript.Compiler.CompilerInterface.CodeGeneration.V1;
using UScript.Compiler.Tools.Extensions;
using UScript.Compiler.Writer;
using UScript.Compiler.Writer.Metadata.V1;
using UScript.Compiler.Writer.V1;
using UScript.Parser;

namespace UScript.Compiler.CompilerInterface.Compilers.V1
{
    public class BasicScriptCompiler : IScriptCompiler
    {
        public IScriptCompilerContext Context { get; set; }

        public BasicScriptCompiler()
        {
            Context = new BasicScriptCompilerContext
            {
                PEWriter = new MemoryPEWriter(),
                
            };

            Context.CodeGen = new BasicCodeGenerator(Context);
        }

        public CompilationResult Compile(byte[] input)
        {
            throw new System.NotImplementedException();
        }

        public CompilationResult Compile(Stream input)
        {
            throw new System.NotImplementedException();
        }

        public CompilationResult Compile(string input)
        {
            throw new System.NotImplementedException();
        }

        public CompilationResult Compile(SourceFile input)
        {
            Context.SourceReader = new StringReader(input.Data);
            return CompileImpl();
        }

        public CompilationResult Compile()
        {
            return null;
        }

        private CompilationResult CompileImpl()
        {
            var inputStream = new AntlrInputStream(Context.SourceReader);
            var lexer = new UScriptLexer(inputStream);
            var tokenStream = new CommonTokenStream(lexer);
            var parser = new UScriptParser(tokenStream);

            var cst = parser.module();
            var listener = new UScriptAstBuilder();

            var walker = new ParseTreeWalker();
            walker.Walk(listener, cst);

            Context.FunctionTable = Context.MetadataContext.FunctionTable = CollectFunctionTable(listener);
            Context.StringTable = Context.MetadataContext.StringTable = CollectStringTable(listener);

            var test = GetFunctionNodes(listener.RootNode);

            var codeGenVisitor = new CodeGeneratorVisitor(Context) { ExceptionNodes = test};

            listener.Accept(codeGenVisitor);
            Context.FunctionTable[0].DeclNode.Accept(new CodeGeneratorVisitor(Context, Context.FunctionTable[0]));

            AssemblePE();

            var output = Context.PEWriter.FinalizeWriter(Context);
            var rawPE = output.ReadStreamFully();

            (Context.PEWriter as IDisposable)?.Dispose();

            Console.WriteLine(listener.ToString());

            return new CompilationResult
            {
                CompiledPE = rawPE
            };
        }

        private List<BaseAstNode> GetFunctionNodes(BaseAstNode rootNode)
        {
            var outList = new List<BaseAstNode>();

            foreach(var node in rootNode.Children)
                if (node is FunctionDeclarationNode)
                    outList.AddRange(GetAllChildNodes(node));

            return outList;
        }

        private List<BaseAstNode> GetAllChildNodes(BaseAstNode rootNode)
        {
            var outList = new List<BaseAstNode> {rootNode};

            foreach (var node in rootNode.Children)
                outList.AddRange(GetAllChildNodes(node));

            return outList;
        }

        private List<FunctionHeader> CollectFunctionTable(UScriptAstBuilder listener)
        {
            var collector = new AST.Visitor.V1.FunctionCollectVisitor(Context.MetadataContext);

            listener.Accept(collector);
            collector.Verify();

            return collector.FunctionTable;
        }

        private List<StringHeader> CollectStringTable(UScriptAstBuilder listener)
        {
            var collector = new AST.Visitor.V1.StringCollectVisitor(Context.MetadataContext);
            listener.Accept(collector);

            return collector.StringTable;
        }

        private void AssemblePE()
        {
            Context.PEWriter.WritePEHeader();
            Context.PEWriter.WriteMetadata(Context.MetadataContext);
            Context.PEWriter.WriteCode(Context);
        }
    }
}
