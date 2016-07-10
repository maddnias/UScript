using UScript.Compiler.AST;

namespace UScript.Compiler.Writer.Metadata.V1
{
    public class ParameterHeader
    {
        public string Name { get; set; }
        public UScriptDataType Type { get; set; }

        public ParameterHeader()
        {
        }

        public ParameterHeader(string name)
        {
            Name = name;
        }
    }
}