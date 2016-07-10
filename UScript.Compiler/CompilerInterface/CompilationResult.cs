using System.Collections.Generic;

namespace UScript.Compiler.CompilerInterface
{
    public class CompilationResult
    {
        public IList<CompilationError> Errors { get; set; }
        public byte[] CompiledPE { get; set; }

        public CompilationResult()
        {
            Errors = new List<CompilationError>();
        }
    }
}