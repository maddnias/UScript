using System.Collections.Generic;
using System.IO;
using UScript.Compiler.AST.Visitor.V1;
using UScript.Compiler.CompilerInterface.CodeGeneration;
using UScript.Compiler.Writer;
using UScript.Compiler.Writer.Metadata;
using UScript.Compiler.Writer.Metadata.V1;

namespace UScript.Compiler.CompilerInterface.Compilers.V1
{
    class BasicScriptCompilerContext : IScriptCompilerContext
    {
        public string OutputPath { get; set; }
        public StringReader SourceReader { get; set; }
        public IPEWriter PEWriter { get; set; }
        public IMetadataContext MetadataContext { get; set; }
        public IList<FunctionHeader> FunctionTable { get; set; }
        public IList<StringHeader> StringTable { get; set; }
        public ICodeGenerator CodeGen { get; set; }

        public BasicScriptCompilerContext()
        {
            MetadataContext = new BasicMetadataContext();
        }
    }
}