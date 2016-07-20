using UScript.Compiler.Writer.DataStructures;

namespace UScript.Compiler.Writer.Metadata
{
    public interface IMetadataToken : IWriteable
    {
        int TokenBase { get; }
        int RawToken { get; set; }
    }
}