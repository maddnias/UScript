using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UScript.Compiler.AST.Visitor;

namespace UScript.Compiler.AST
{
    public abstract class BaseAstNode : IAstElement
    {
        public BaseAstNode Parent { get; set; }
        public IList<BaseAstNode> Children { get; set; }

        protected BaseAstNode()
        {
            Children = new List<BaseAstNode>();
        }

        public override string ToString()
        {
            return GetType().Name;
        }

        public abstract void Accept(AstVisitor visitor);
    }
}
