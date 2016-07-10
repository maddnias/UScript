using System.IO;

namespace UScript.Compiler.CompilerInterface
{
    public sealed class SourceFile
    {
        public string Path { get; set; }

        public string Data => File.ReadAllText(Path);

        public SourceFile(string path)
        {
            Path = path;
        }
    }
}
