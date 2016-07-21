using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Antlr4.Runtime;
using UScript.Compiler.AST;
using UScript.Parser;

namespace UScript.Compiler.Tools.Extensions
{
    public static class AstBuilderExtensions
    {
        public static UScriptDataType UScriptTypeFromString(this string str)
        {
            if (string.IsNullOrEmpty(str))
                return UScriptDataType.RuntimeDetermined;

            switch (str)
            {
                case "Byte":
                    return UScriptDataType.Byte;
                case "Char":
                    return UScriptDataType.Char;
                case "I32":
                    return UScriptDataType.I32;
                //case "String":
                //    return UScriptDataType.String;
                //case "Float":
                //    return UScriptDataType.Float;
            }

            throw new ArgumentOutOfRangeException(nameof(str));
        }
    }
}
