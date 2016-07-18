using System;
using System.Collections.Generic;
using System.IO;
using System.Text;
using UScript.Compiler.AST;
using UScript.Compiler.AST.Visitor.V1;
using UScript.Compiler.CompilerInterface.CodeGeneration.V1;
using UScript.Compiler.CompilerInterface.Compilers.V1;
using UScript.Compiler.Writer.DataStructures;

namespace UScript.Compiler.Writer.Metadata.V1
{
    public class FunctionHeader : IRow
    {
        public string Name { get; set; }
        public bool IsEntrypoint { get; set; }
        public List<ParameterHeader> Parameters { get; set; }
        public FunctionMetadataToken Token { get; set; }
        public FunctionDeclarationNode DeclNode { get; set; }
        public FunctionCodeGenerator CodeGen { get; set; }
        public MetadataAddress CodeAddress { get; set; }
        public MetadataAddress BlobAddress { get; set; }

        public FunctionHeader()
        {
            Parameters = new List<ParameterHeader>();
            CodeAddress = MetadataAddress.Empty;
        }

        public void WriteTo(Stream dest)
        {
            dest.Write(BitConverter.GetBytes(Name.Length), 0, sizeof(int));
            dest.Write(Encoding.ASCII.GetBytes(Name), 0, Name.Length);
            dest.WriteByte(IsEntrypoint ? (byte)0x1 : (byte)0x0);
            BlobAddress.WriteTo(dest);
            CodeAddress.WriteTo(dest);
        }
    }
}
