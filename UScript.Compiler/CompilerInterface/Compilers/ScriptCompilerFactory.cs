using System;

namespace UScript.Compiler.CompilerInterface.Compilers
{
    /// <summary>
    /// Factory class to create a script compiler based on version
    /// </summary>
    public static class ScriptCompilerFactory
    {
        /// <summary>
        /// Creates and returns a compiler based on version
        /// </summary>
        /// <param name="version">The version of compiler to use</param>
        /// <returns>The created script compiler</returns>
        public static IScriptCompiler CreateCompiler(Version version)
        {
            if (version <= new Version(1, 0))
            {
                return new V1.BasicScriptCompiler();
            }

            throw new ArgumentOutOfRangeException(nameof(version));
        }
    }
}
