using UScript.Compiler.AST.Visitor;
using UScript.Parser;

namespace UScript.Compiler.AST
{
    public class ArgumentDeclarationNode : BaseAstNode
    {
        public ExpressionNode Exp { get; set; }
        public override void Accept(AstVisitor visitor)
        {
            visitor.VisitArgumentDeclarationNode(this);
        }
    }
}