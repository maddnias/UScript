using System;
using UScript.Compiler.AST.Visitor;

namespace UScript.Compiler.AST
{
    public class ArgumentListNode : BaseAstNode
    {
        public override void Accept(AstVisitor visitor)
        {
            visitor.VisitArgumentListNode(this);
        }
    }
}