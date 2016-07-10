using System;
using UScript.Compiler.AST.Visitor;
using UScript.Compiler.Writer.Metadata.V1;

namespace UScript.Compiler.AST
{
    public class FunctionCallStatementNode : BaseAstNode
    {
        public string FunctionName { get; set; }
        public FunctionMetadataToken Token { get; set; }

        public override void Accept(AstVisitor visitor)
        {
            visitor.VisitFunctionCallStatementNode(this);
        }
    }
}