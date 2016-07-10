using System;
using UScript.Compiler.AST.Visitor;
using UScript.Parser;

namespace UScript.Compiler.AST
{
    public class VariableDeclarationNode : BaseAstNode
    {
        public string Name { get; set; }
        public ExpressionNode InitDataExp { get; set; }

        public override void Accept(AstVisitor visitor)
        {
            visitor.VisitVariableDeclarationNode(this);
        }
    }
}