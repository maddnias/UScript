using UScript.Compiler.Writer.DataStructures;

namespace UScript.Compiler.Writer.Metadata
{
    public interface IMetadataToken : IWriteable
    {
        long TokenBase { get; }
        long RawToken { get; set; }
    }
}