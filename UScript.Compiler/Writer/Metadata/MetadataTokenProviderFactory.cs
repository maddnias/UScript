using System;
using UScript.Compiler.Writer.Metadata.V1;

namespace UScript.Compiler.Writer.Metadata
{
    public static class MetadataTokenProviderFactory
    {
        public static IMetadataTokenProvider<T> Create<T>(Version ver) where T : IMetadataToken
        {
            if (ver <= new Version(1, 0))
            {
                if (typeof(T) == typeof(FunctionMetadataToken))
                    return new FunctionTokenProvider() as IMetadataTokenProvider<T>;
            }

            throw new ArgumentOutOfRangeException(nameof(ver));
        }
    }
}
