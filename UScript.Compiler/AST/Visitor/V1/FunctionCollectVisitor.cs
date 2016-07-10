using System.Collections.Generic;
using System.Linq;
using UScript.Compiler.Exceptions.AST;
using UScript.Compiler.Tools.Extensions;
using UScript.Compiler.Writer.Metadata.V1;

namespace UScript.Compiler.AST.Visitor.V1
{
    public class FunctionCollectVisitor : AstVisitor
    {
        public List<FunctionHeader> FunctionTable { get; set; }
        public IMetadataContext MetadataContext { get; set; }

        public FunctionCollectVisitor(IMetadataContext context)
        {
            FunctionTable = new List<FunctionHeader>();
            MetadataContext = context;
        }

        public void Verify()
        {
            int epCount;
            if ((epCount = FunctionTable.Count(x => x.IsEntrypoint)) > 1)
            {
                throw new MultipleEntrypointsDefinedException(epCount.ToString());
            }

            var duplicateKeys = FunctionTable.GroupBy(x => x.Name)
                .Where(group => group.Count() > 1)
                .Select(group => group.Key).ToList();

            if (duplicateKeys.Any())
            {
                throw new FunctionAlreadyDefinedException(duplicateKeys.First());
            }
        }

        public override void VisitArgumentDeclarationNode(ArgumentDeclarationNode node)
        {
        }

        public override void VisitArgumentListNode(ArgumentListNode node)
        {
        }

        public override void VisitArithmeticExpressionNode(ArithmeticExpressionNode node)
        {
        }

        public override void VisitExpressionNode(ExpressionNode node)
        {
        }

        public override void VisitFunctionCallStatementNode(FunctionCallStatementNode node)
        {

        }

        public override void VisitFunctionDeclarationNode(FunctionDeclarationNode node)
        {
            var ctx = new FunctionHeader
            {
                Name = node.Name,
                IsEntrypoint = node.Name.ToLower() == "main",
                Token = MetadataContext.FunctionTokenProvider.GenerateToken(),
                DeclNode = node
            };

            FunctionTable.Add(ctx);
        }

        public override void VisitParameterDeclarationNode(ParameterDeclarationNode node)
        {
            FunctionTable.Last().Parameters.Add(new ParameterHeader
            {
                Name = node.Name,
                Type = node.Type.UScriptTypeFromString()
            });
        }

        public override void VisitParameterListNode(ParameterListNode node)
        {
        }

        public override void VisitReturnStatementNode(ReturnStatementNode node)
        {
        }

        public override void VisitVariableDeclarationNode(VariableDeclarationNode node)
        {
            
        }

        public override void VisitStringNode(StringNode node)
        {
      
        }

        public override void VisitNumberExpressionNode(NumberExpressionNode node)
        {

        }

        public override void VisitVariableReferenceNode(VariableReferenceNode node)
        {
            
        }
    }
}