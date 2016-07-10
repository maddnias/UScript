using System.Collections.Generic;
using System.IO;
using UScript.Compiler.AST.Visitor.V1;
using UScript.Compiler.CompilerInterface.CodeGeneration;
using UScript.Compiler.Writer;
using UScript.Compiler.Writer.Metadata;
using UScript.Compiler.Writer.Metadata.V1;

namespace UScript.Compiler.CompilerInterface
{
    public interface IScriptCompilerContext
    {
        string OutputPath { get; set; }
        StringReader SourceReader { get; set; }
        IPEWriter PEWriter { get; set; }
        IMetadataContext MetadataContext { get; set; }
        IList<FunctionHeader> FunctionTable { get; set; }
        IList<StringHeader> StringTable { get; set; }
        ICodeGenerator CodeGen { get; set; }
    }
}
