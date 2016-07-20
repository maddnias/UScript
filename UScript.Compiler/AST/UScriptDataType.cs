using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace UScript.Compiler.AST
{
    public enum UScriptDataType
    {
        RuntimeDetermined,
        Byte,
        Char,
        Bool,
        I16,
        I32,
        I64,
        U16,
        U32,
        U64,
        Void,
        Undefined
    }
}
