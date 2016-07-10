using System;
using System.IO;

namespace UScript.Compiler.Writer.Metadata.V1
{
    public class MemoryMetadataWriter : IMetadataWriter
    {
        public byte[] WriteFunctionTable(IMetadataContext ctx)
        {
            using (var ms = new MemoryStream())
            {
                foreach (var row in ctx.FunctionTable)
                {
                    var blobAddr = ctx.BlobWriter.WriteFunctionSignature(row);
                    row.BlobAddress = blobAddr;
                    row.WriteTo(ms);
                }

                return ms.ToArray();
            }
        }

        public byte[] WriteStringTable(IMetadataContext ctx)
        {

            return null;
        }

        public void WriteFunctionCode(IMetadataContext ctx)
        {

        }
    }
}
