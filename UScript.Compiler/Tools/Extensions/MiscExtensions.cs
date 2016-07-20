using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using UScript.Compiler.Writer.Metadata;

namespace UScript.Compiler.Tools.Extensions
{
    public static class MiscExtensions
    {
        public static int GetRealToken(this IMetadataToken token)
        {
            return token.TokenBase + token.RawToken;
        }

        public static byte[] ReadStreamFully(this Stream stream)
        {
            stream.Position = 0;
            var buffer = new byte[16*1024];
            using (var ms = new MemoryStream())
            {
                int read;
                while ((read = stream.Read(buffer, 0, buffer.Length)) > 0)
                {
                    ms.Write(buffer, 0, read);
                }
                return ms.ToArray();
            }
        }
    }
}
