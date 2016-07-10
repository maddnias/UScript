using System.Collections.Generic;

namespace UScript.Compiler.AST.Visitor
{
    public abstract class AstVisitor
    {
        public List<BaseAstNode> ExceptionNodes { get; set; }

        protected AstVisitor()
        {
            ExceptionNodes = new List<BaseAstNode>();
        }

        public abstract void VisitArgumentDeclarationNode(ArgumentDeclarationNode node);
        public abstract void VisitArgumentListNode(ArgumentListNode node);
        public abstract void VisitArithmeticExpressionNode(ArithmeticExpressionNode node);
        public abstract void VisitExpressionNode(ExpressionNode node);
        public abstract void VisitFunctionCallStatementNode(FunctionCallStatementNode node);
        public abstract void VisitFunctionDeclarationNode(FunctionDeclarationNode node);
        public abstract void VisitParameterDeclarationNode(ParameterDeclarationNode node);
        public abstract void VisitParameterListNode(ParameterListNode node);
        public abstract void VisitReturnStatementNode(ReturnStatementNode node);
        public abstract void VisitVariableDeclarationNode(VariableDeclarationNode node);
        public abstract void VisitStringNode(StringNode node);
        public abstract void VisitNumberExpressionNode(NumberExpressionNode node);
        public abstract void VisitVariableReferenceNode(VariableReferenceNode node);
    }
}
