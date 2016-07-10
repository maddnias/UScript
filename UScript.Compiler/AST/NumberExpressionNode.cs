using UScript.Compiler.AST.Visitor;
using UScript.Parser;

namespace UScript.Compiler.AST
{
    public class NumberExpressionNode : ExpressionNode
    {
        public UScriptParser.NumberContext Context { get; set; }

        public override void Accept(AstVisitor visitor)
        {
            visitor.VisitNumberExpressionNode(this);
        }
    }
}