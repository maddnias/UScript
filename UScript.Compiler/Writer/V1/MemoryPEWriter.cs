using System;
using System.IO;
using UScript.Compiler.CompilerInterface;

namespace UScript.Compiler.Writer.V1
{
    public class MemoryPEWriter : IPEWriter, IDisposable
    {
        private readonly MemoryStream _peStream;

        public DataStructures.V1.UScriptPEHeader Header { get; set; }
        public Metadata.V1.IMetadataWriter MetadataWriter { get; set; }

        public MemoryPEWriter()
        {
            _peStream = new MemoryStream();
            MetadataWriter = new Metadata.V1.MemoryMetadataWriter();
            Header = new DataStructures.V1.UScriptPEHeader();
        }

        public void WritePEHeader()
        {
            // Just allocate space
            Header.WriteTo(_peStream);
        }

        public void WriteMetadata(Metadata.V1.IMetadataContext ctx)
        {
            var funcTable = MetadataWriter.WriteFunctionTable(ctx);
            var stringTable = MetadataWriter.WriteStringTable(ctx);

            Header.FunctionTableAddress = new Metadata.MetadataAddress((ulong)(ctx.MetadataStream.Position + _peStream.Position));
            ctx.MetadataStream.Write(funcTable, 0, funcTable.Length);

            Header.StringTableAddress = new Metadata.MetadataAddress((ulong) (ctx.MetadataStream.Position + _peStream.Position));
            //ctx.MetadataStream.Write(stringTable, 0, stringTable.Length);

            Header.BlobAddress = new Metadata.MetadataAddress((ulong) (ctx.MetadataStream.Position + _peStream.Position));
            ctx.MetadataStream.Write(ctx.BlobWriter.BlobData, 0, ctx.BlobWriter.BlobData.Length);

            ctx.MetadataStream.Position = 0;
            ctx.MetadataStream.CopyTo(_peStream);
            ctx.MetadataStream.Dispose();
        }

        public void WriteCode(IScriptCompilerContext ctx)
        {
            Header.CodeStart = new Metadata.MetadataAddress((ulong)_peStream.Position);
            _peStream.Write(ctx.CodeGen.Code, 0, ctx.CodeGen.Code.Length);

            foreach (var function in ctx.FunctionTable)
            {
                function.CodeAddress = new Metadata.MetadataAddress((ulong) _peStream.Position);
                _peStream.Write(function.CodeGen.Code, 0, function.CodeGen.Code.Length);
            }
        }

        public Stream FinalizeWriter(IScriptCompilerContext ctx)
        {
            _peStream.Dispose();

            var finalPE = new MemoryStream();
            Header.WriteTo(finalPE);

            // Metadata

            foreach (var function in ctx.MetadataContext.FunctionTable)
            {
                function.WriteTo(finalPE);
            }

            finalPE.Write(ctx.MetadataContext.BlobWriter.BlobData, 0, ctx.MetadataContext.BlobWriter.BlobData.Length);
            finalPE.Write(ctx.CodeGen.Code, 0, ctx.CodeGen.Code.Length);

            // Code
            foreach (var function in ctx.MetadataContext.FunctionTable)
            {
                finalPE.Write(function.CodeGen.Code, 0, function.CodeGen.Code.Length);
            }

            return finalPE;

        }

        public void Dispose()
        {
            _peStream.Dispose();
        }
    }
}
