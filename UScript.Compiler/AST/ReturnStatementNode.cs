using System;
using UScript.Compiler.AST.Visitor;
using UScript.Parser;

namespace UScript.Compiler.AST
{
    public class ReturnStatementNode : BaseAstNode
    {
        public override void Accept(AstVisitor visitor)
        {
            visitor.VisitReturnStatementNode(this);
        }
    }
}