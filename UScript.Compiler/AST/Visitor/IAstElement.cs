using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace UScript.Compiler.AST.Visitor
{
    public interface IAstElement
    {
        void Accept(AstVisitor visitor);
    }
}
