using UScript.Compiler.Writer.Metadata;

namespace UScript.Compiler.CompilerInterface.CodeGeneration.V1
{
    public sealed class FunctionReference : IMemberReference
    {
        public IMetadataToken MetadataToken { get; set; }
    }
}
