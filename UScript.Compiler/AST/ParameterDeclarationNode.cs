using System;
using UScript.Compiler.AST.Visitor;

namespace UScript.Compiler.AST
{
    public class ParameterDeclarationNode : BaseAstNode
    {
        public string Name { get; set; }
        public string Type { get; set; }

        public override void Accept(AstVisitor visitor)
        {
            visitor.VisitParameterDeclarationNode(this);
        }
    }
}