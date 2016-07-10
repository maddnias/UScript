using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using UScript.Compiler.CompilerInterface;
using UScript.Compiler.Writer.DataStructures;
using UScript.Compiler.Writer.Metadata.V1;

namespace UScript.Compiler.Writer
{
    public interface IPEWriter
    {
        IMetadataWriter MetadataWriter { get; set; }

        void WritePEHeader();
        void WriteMetadata(IMetadataContext ctx);
        void WriteCode(IScriptCompilerContext ctx);

        Stream FinalizeWriter(IScriptCompilerContext ctx);
    }
}
