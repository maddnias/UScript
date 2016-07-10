using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UScript.Compiler.AST;

namespace UScript.Compiler.CompilerInterface.CodeGeneration.V1
{
    public class LocalVariable : IVariable
    {
        public int Index { get; set; }
        public string Name { get; set; }
        public UScriptDataType Type { get; set; }
    }
}
