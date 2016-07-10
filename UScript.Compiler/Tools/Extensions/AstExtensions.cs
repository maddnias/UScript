using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UScript.Compiler.AST;

namespace UScript.Compiler.Tools.Extensions
{
    public static class AstExtensions
    {
        public static BaseAstNode GetSuperNode(this BaseAstNode node)
        {
            while (node.Parent != null)
                node = node.Parent;

            return node;
        }
    }
}
