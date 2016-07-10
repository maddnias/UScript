using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UScript.Compiler.Writer.Metadata;

namespace UScript.Compiler.CompilerInterface.CodeGeneration
{
    public interface IMemberReference
    {
        IMetadataToken MetadataToken { get; set; }
    }
}
