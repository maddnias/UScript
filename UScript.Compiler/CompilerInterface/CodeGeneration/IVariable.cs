using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UScript.Compiler.AST;

namespace UScript.Compiler.CompilerInterface.CodeGeneration
{
    public interface IVariable
    {
        int Index { get; set; }
        string Name { get; set; }
        UScriptDataType Type { get; set; }
    }
}
