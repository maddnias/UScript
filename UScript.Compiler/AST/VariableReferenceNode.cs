using System;
using UScript.Compiler.AST.Visitor;
using UScript.Parser;

namespace UScript.Compiler.AST
{
    public enum ReferenceType
    {
        Variable,
        Parameter
    }

    public class VariableReferenceNode : BaseAstNode
    {
        public string Name { get; set; }
        public ReferenceType ReferenceType { get; set; }

        public VariableReferenceNode()
        {
        }

        public override void Accept(AstVisitor visitor)
        {
            visitor.VisitVariableReferenceNode(this);
        }
    }
}