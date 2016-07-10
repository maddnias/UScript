namespace UScript.Compiler.Writer.Metadata
{
    public interface IMetadataTokenProvider<out T> where T : IMetadataToken
    {
        int TokenCounter { get; set; }
        T GenerateToken();
    }
}
