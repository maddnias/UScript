using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UScript.Compiler.Writer.Metadata;
using UScript.Compiler.Writer.Metadata.V1;

namespace UScript.Compiler.AST.Visitor.V1
{
    public class StringCollectVisitor : AstVisitor
    {
        public List<Writer.Metadata.V1.StringHeader> StringTable { get; set; }
        public IMetadataContext MetadataContext { get; set; }


        public StringCollectVisitor(IMetadataContext context)
        {
            StringTable = new List<Writer.Metadata.V1.StringHeader>();
            MetadataContext = context;
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
          
        }

        public override void VisitParameterDeclarationNode(ParameterDeclarationNode node)
        {
      
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
            if (StringTable.All(x => x.Data != node.Data.Replace("\"", null)))
                StringTable.Add(new Writer.Metadata.V1.StringHeader
                {
                    Data = node.Data.Replace("\"", null),
                    Token = MetadataContext.StringTokenProvider.GenerateToken()
                });
        }

        public override void VisitNumberExpressionNode(NumberExpressionNode node)
        {
        }

        public override void VisitVariableReferenceNode(VariableReferenceNode node)
        {
            
        }
    }
}
