using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using UScript.Compiler.Writer.Metadata;
using UScript.Compiler.Writer.Metadata.V1;

namespace UScript.Compiler.Writer.V1
{
    public class MemoryBlobWriter : IBlobWriter, IDisposable
    {
        public byte[] BlobData => _blob.ToArray();

        private readonly MemoryStream _blob;

        public MemoryBlobWriter()
        {
            _blob = new MemoryStream();
        }

        public MetadataAddress WriteFunctionSignature(IRow sourceRow)
        {
            var header = sourceRow as FunctionHeader;
            var addr = new MetadataAddress((ulong) _blob.Position);

            if (header == null)
                throw new ArgumentException(nameof(sourceRow));

            header.BlobAddress = addr;
            _blob.Write(BitConverter.GetBytes(header.Parameters.Count), 0, sizeof(int));

            foreach (var param in header.Parameters)
                _blob.WriteByte((byte) param.Type);

            return addr;
        }

        public void Dispose()
        {
            _blob.Dispose();
        }
    }
}
