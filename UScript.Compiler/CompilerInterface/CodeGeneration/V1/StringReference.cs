using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UScript.Compiler.Writer.Metadata;

namespace UScript.Compiler.CompilerInterface.CodeGeneration.V1
{
    class StringReference : IMemberReference
    {
        public IMetadataToken MetadataToken { get; set; }
    }
}
