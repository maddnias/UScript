using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UScript.Compiler.AST.Visitor;

namespace UScript.Compiler.AST
{
    public class FunctionDeclarationNode : BaseAstNode
    {
        public string Name { get; set; }

        public override void Accept(AstVisitor visitor)
        {
            visitor.VisitFunctionDeclarationNode(this);
        }
    }
}
