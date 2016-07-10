using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace UScript.Compiler.Writer.Metadata.V1
{
    public class StringHeader : IRow
    {
        public string Data { get; set; }
        public StringMetadataToken Token { get; set; }
        public void WriteTo(Stream dest)
        {
            throw new NotImplementedException();
        }
    }
}
