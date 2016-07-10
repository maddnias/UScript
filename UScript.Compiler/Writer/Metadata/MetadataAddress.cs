using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using UScript.Compiler.Writer.DataStructures;

namespace UScript.Compiler.Writer.Metadata
{
    public class MetadataAddress : IWriteable
    {
        public static MetadataAddress Empty => new MetadataAddress(0);
        public ulong Address { get; }

        public MetadataAddress(ulong address)
        {
            Address = address;
        }

        public void WriteTo(Stream dest)
        {
            dest.Write(BitConverter.GetBytes(Address), 0, sizeof(ulong));
        }
    }
}
