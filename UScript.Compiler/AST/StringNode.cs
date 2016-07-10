using UScript.Compiler.AST.Visitor;

namespace UScript.Compiler.AST
{
    public class StringNode : BaseAstNode
    {
        public string Data { get; set; }

        public override void Accept(AstVisitor visitor)
        {
            visitor.VisitStringNode(this);
        }
    }
}