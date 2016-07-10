using System;
using System.Collections.Generic;
using System.IO;
using UScript.Compiler.AST.Visitor.V1;
using UScript.Compiler.CompilerInterface;
using UScript.Compiler.CompilerInterface.Compilers.V1;
using UScript.Compiler.Writer.V1;

namespace UScript.Compiler.Writer.Metadata.V1
{
    public class BasicMetadataContext : IMetadataContext
    {
        public Stream MetadataStream { get; set; }
        public ICollection<string> ReferencedStrings { get; set; }
        public IMetadataTokenProvider<FunctionMetadataToken> FunctionTokenProvider { get; set; }
        public IMetadataTokenProvider<StringMetadataToken> StringTokenProvider { get; set; }
        public IList<FunctionHeader> FunctionTable { get; set; }
        public IList<StringHeader> StringTable { get; set; }
        public IBlobWriter BlobWriter { get; set; }
        public ICollection<FunctionHeader> FunctionHeaderTable { get; set; }

        public BasicMetadataContext()
        {
            MetadataStream = new MemoryStream();
            ReferencedStrings = new List<string>();
            FunctionTokenProvider = MetadataTokenProviderFactory.Create<FunctionMetadataToken>(new System.Version(1, 0));
            BlobWriter = new MemoryBlobWriter();
            FunctionHeaderTable = new List<FunctionHeader>();
            StringTable = new List<StringHeader>();
            //   StringTokenProvider = MetadataTokenProviderFactory.Create<StringMetadataToken>(new System.Version(1, 0));
        }

        public void Dispose()
        {
            (BlobWriter as IDisposable)?.Dispose();
            MetadataStream.Dispose();
        }
    }
}