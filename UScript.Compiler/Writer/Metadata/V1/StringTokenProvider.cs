namespace UScript.Compiler.Writer.Metadata.V1
{
    public sealed class StringTokenProvider : IMetadataTokenProvider<StringMetadataToken>
    {
        public int TokenCounter { get; set; }

        public StringTokenProvider()
        {
            TokenCounter = 0;
        }

        public StringMetadataToken GenerateToken()
        {
            var tok = new StringMetadataToken();
            tok.RawToken = tok.TokenBase + ++TokenCounter;

            return tok;
        }
    }
}