namespace UScript.Compiler.Writer.Metadata.V1
{
    public sealed class FunctionTokenProvider : IMetadataTokenProvider<FunctionMetadataToken>
    {
        public int TokenCounter { get; set; }

        public FunctionTokenProvider()
        {
            TokenCounter = 0;
        }

        public FunctionMetadataToken GenerateToken()
        {
            var tok = new FunctionMetadataToken();
            tok.RawToken = tok.TokenBase + ++TokenCounter;

            return tok;
        }
    }
}