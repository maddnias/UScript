﻿using System;
using System.IO;

namespace UScript.Compiler.Writer.Metadata.V1
{
    public sealed class FunctionMetadataToken : IMetadataToken
    {
        public int TokenBase => 0x1000;
        public int RawToken { get; set; }
        public void WriteTo(Stream dest)
        {
            dest.Write(BitConverter.GetBytes(RawToken), 0, sizeof(int));
        }

        public override string ToString()
        {
            return RawToken.ToString("X4");
        }
    }
}