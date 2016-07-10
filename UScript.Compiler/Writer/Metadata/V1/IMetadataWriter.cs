namespace UScript.Compiler.Writer.Metadata.V1
{
    public interface IMetadataWriter
    {
        byte[] WriteFunctionTable(IMetadataContext ctx);
        byte[] WriteStringTable(IMetadataContext ctx);
    }
}
