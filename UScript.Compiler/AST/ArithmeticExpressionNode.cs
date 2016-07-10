using System;
using UScript.Compiler.AST.Visitor;
using UScript.Parser;

namespace UScript.Compiler.AST
{
    public enum ArithmeticOp
    {
        Add,
        Subtract,
    }

    public class ArithmeticExpressionNode : BaseAstNode
    {
        public ArithmeticOp Op { get; set; }
        public UScriptParser.ExpContext Left { get; set; }
        public UScriptParser.ExpContext Right { get; set; }

        public override void Accept(AstVisitor visitor)
        {
            visitor.VisitArithmeticExpressionNode(this);
        }
    }
}