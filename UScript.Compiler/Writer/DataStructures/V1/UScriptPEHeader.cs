using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using UScript.Compiler.Writer.Metadata;

namespace UScript.Compiler.Writer.DataStructures.V1
{
    public class UScriptPEHeader : IWriteable
    {
        public const long Magic = 0x0BBE1010BBE101;
        public MetadataAddress CodeStart { get; set; }
        public MetadataAddress FunctionTableAddress { get; set; }
        public MetadataAddress StringTableAddress { get; set; }
        public MetadataAddress BlobAddress { get; set; }

        public UScriptPEHeader()
        {
            CodeStart = MetadataAddress.Empty;
            FunctionTableAddress = MetadataAddress.Empty;
            StringTableAddress = MetadataAddress.Empty;
            BlobAddress = MetadataAddress.Empty;
        }

        public void WriteTo(Stream dest)
        {
            dest.Write(BitConverter.GetBytes(Magic), 0, sizeof(long));
            CodeStart.WriteTo(dest);
            FunctionTableAddress.WriteTo(dest);
            StringTableAddress.WriteTo(dest);
            BlobAddress.WriteTo(dest);
        }
    }
}
