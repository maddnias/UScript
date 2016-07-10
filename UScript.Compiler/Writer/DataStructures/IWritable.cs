using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace UScript.Compiler.Writer.DataStructures
{
    public interface IWriteable
    {
        void WriteTo(Stream dest);
    }
}
