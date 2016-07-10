using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UScript.Compiler.Writer.Metadata;

namespace UScript.Compiler.Writer
{
    public interface IBlobWriter
    {
        byte[] BlobData { get; }
        MetadataAddress WriteFunctionSignature(IRow sourceRow);
    }
}
