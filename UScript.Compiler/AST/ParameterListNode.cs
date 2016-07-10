using System;
using UScript.Compiler.AST.Visitor;

namespace UScript.Compiler.AST
{
    public class ParameterListNode : BaseAstNode
    {
        public override void Accept(AstVisitor visitor)
        {
            visitor.VisitParameterListNode(this);
        }
    }
}