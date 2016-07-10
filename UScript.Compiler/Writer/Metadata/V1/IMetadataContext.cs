using System;
using System.Collections.Generic;
using System.IO;
using UScript.Compiler.CompilerInterface;

namespace UScript.Compiler.Writer.Metadata.V1
{
    public interface IMetadataContext : IDisposable
    {
        Stream MetadataStream { get; set; }
        ICollection<string> ReferencedStrings { get; set; }
        IMetadataTokenProvider<FunctionMetadataToken> FunctionTokenProvider { get; set; }
        IMetadataTokenProvider<StringMetadataToken> StringTokenProvider { get; set; }
        IList<FunctionHeader> FunctionTable { get; set; }
        IList<StringHeader> StringTable { get; set; }
        IBlobWriter BlobWriter { get; set; }
    }
}
