using System.IO;

namespace UScript.Compiler.CompilerInterface
{
    public interface IScriptCompiler
    {
        IScriptCompilerContext Context { get; set; }
        CompilationResult Compile(byte[] input);
        CompilationResult Compile(Stream input);
        CompilationResult Compile(string input);
        CompilationResult Compile(SourceFile input);
    }
}
