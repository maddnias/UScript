using System;
using Antlr4.Runtime.Misc;
using UScript.Compiler.AST;
using UScript.Compiler.AST.Visitor;
using UScript.Compiler.Tools.Extensions;
using UScript.Parser;

namespace UScript.Compiler
{
    public class UScriptAstBuilder : UScriptBaseListener
    {
        public BaseAstNode RootNode => _currentNode.GetSuperNode();

        private BaseAstNode _currentNode;

        public UScriptAstBuilder()
        {
            _currentNode = new RootNode();
        }

        public void Accept(AstVisitor visitor)
        {
            RecursiveAccept(RootNode, visitor);
        }

        private void RecursiveAccept(BaseAstNode node, AstVisitor visitor)
        {
            if(!visitor.ExceptionNodes.Contains(node))
                node.Accept(visitor);

            foreach (var child in node.Children)
                RecursiveAccept(child, visitor);
        }

        public override void EnterFunctionDeclStatement([NotNull] UScriptParser.FunctionDeclStatementContext context)
        {
            AddNode(new FunctionDeclarationNode
            {
                Name = context.name.GetText()
            });

            base.EnterFunctionDeclStatement(context);
        }

        public override void ExitFunctionDeclStatement([NotNull] UScriptParser.FunctionDeclStatementContext context)
        {
            TraverseUp();

            base.ExitFunctionDeclStatement(context);
        }

        public override void EnterVarDeclStatement([NotNull] UScriptParser.VarDeclStatementContext context)
        {
            AddNode(new VariableDeclarationNode
            {
                Name = context.GetRuleContext<UScriptParser.VarDeclContext>(0).name.Text
             //   InitDataExp = context.GetRuleContext<UScriptParser.VarDeclContext>(0).initData
            });

            base.EnterVarDeclStatement(context);
        }

        public override void ExitVarDeclStatement([NotNull] UScriptParser.VarDeclStatementContext context)
        {
            TraverseUp();

            base.ExitVarDeclStatement(context);
        }

        public override void EnterReturnStatement([NotNull] UScriptParser.ReturnStatementContext context)
        {
            AddNode(new ReturnStatementNode());

            base.EnterReturnStatement(context);
        }

        public override void ExitReturnStatement([NotNull] UScriptParser.ReturnStatementContext context)
        {
            TraverseUp();

            base.ExitReturnStatement(context);
        }

        public override void EnterParlist([NotNull] UScriptParser.ParlistContext context)
        {
            if(context.GetRuleContexts<UScriptParser.ParamContext>().Length > 0)
                AddNode(new ParameterListNode());

            base.EnterParlist(context);
        }

        public override void ExitParlist([NotNull] UScriptParser.ParlistContext context)
        {
            TraverseUp();

            base.ExitParlist(context);
        }

        public override void EnterParam([NotNull] UScriptParser.ParamContext context)
        {
            AddNode(new ParameterDeclarationNode
            {
                Name = context.GetRuleContext<UScriptParser.VarContext>(0).GetText(),
                Type = context.paramType?.GetText()
            });

            base.EnterParam(context);
        }

        public override void ExitParam([NotNull] UScriptParser.ParamContext context)
        {
            TraverseUp();

            base.ExitParam(context);
        }

        public override void EnterAddSubExp([NotNull] UScriptParser.AddSubExpContext context)
        {
            var node = new ArithmeticExpressionNode
            {
                Op = ArithmeticOp.Add
            };

            if (context.GetRuleContext<UScriptParser.OperatorAddSubContext>(0).GetText() == "-")
            {
                node.Op = ArithmeticOp.Subtract;
            }

            AddNode(node);

            base.EnterAddSubExp(context);
        }

        public override void ExitAddSubExp([NotNull] UScriptParser.AddSubExpContext context)
        {
            TraverseUp();

            base.ExitAddSubExp(context);
        }

        public override void EnterMulDivModExp([NotNull] UScriptParser.MulDivModExpContext context)
        {
            var node = new ArithmeticExpressionNode
            {
                Op = ArithmeticOp.Mul
            };

            if (context.GetRuleContext<UScriptParser.OperatorMulDivModContext>(0).GetText() == "/")
            {
                node.Op = ArithmeticOp.Div;
            }

            AddNode(node);

            base.EnterMulDivModExp(context);
        }

        public override void ExitMulDivModExp([NotNull] UScriptParser.MulDivModExpContext context)
        {
            TraverseUp();

            base.ExitMulDivModExp(context);
        }

        public override void EnterFuncCallStatement([NotNull] UScriptParser.FuncCallStatementContext context)
        {
            var actualCall = context.GetRuleContext<UScriptParser.FunctioncallContext>(0);
            AddNode(new FunctionCallStatementNode { FunctionName = actualCall.target.GetText() });

            base.EnterFuncCallStatement(context);
        }

        public override void ExitFuncCallStatement([NotNull] UScriptParser.FuncCallStatementContext context)
        {
            TraverseUp();

            base.ExitFuncCallStatement(context);
        }

        public override void EnterArgList([NotNull] UScriptParser.ArgListContext context)
        {
            var argListNode = new ArgumentListNode();
            var expList = context.GetRuleContext<UScriptParser.ExplistContext>(0);

            //foreach (var exp in expList.GetRuleContexts<UScriptParser.ExpContext>())
            //{
            //    argListNode.Children.Add(new ArgumentDeclarationNode
            //    {
                    
            //    });
            //}

            AddNode(argListNode);

            base.EnterArgList(context);
        }

        public override void ExitArgList([NotNull] UScriptParser.ArgListContext context)
        {
            TraverseUp();
            
            base.ExitArgList(context);
        }

        public override void EnterStringExp([NotNull] UScriptParser.StringExpContext context)
        {
            AddNode(new StringNode {Data = context.GetRuleContext<UScriptParser.StringContext>(0).strData.Text});

            base.EnterStringExp(context);
        }

        public override void ExitStringExp([NotNull] UScriptParser.StringExpContext context)
        {
            TraverseUp();

            base.ExitStringExp(context);
        }

        public override void EnterNumberExp([NotNull] UScriptParser.NumberExpContext context)
        {
            AddNode(new NumberExpressionNode {Context = context.GetRuleContext<UScriptParser.NumberContext>(0)});

            base.EnterNumberExp(context);
        }

        public override void ExitNumberExp([NotNull] UScriptParser.NumberExpContext context)
        {
            TraverseUp();

            base.ExitNumberExp(context);
        }

        public override void EnterTesterexp([NotNull] UScriptParser.TesterexpContext context)
        {
            var lol = context.exp();
            base.EnterTesterexp(context);
        }

        public override void EnterVarExp([NotNull] UScriptParser.VarExpContext context)
        {
            AddNode(new VariableReferenceNode {Name = context.var().NAME().GetText()});

            base.EnterVarExp(context);
        }

        public override void ExitVarExp([NotNull] UScriptParser.VarExpContext context)
        {
            TraverseUp();

            base.ExitVarExp(context);
        }

        private void AddNode<T>(T node) where T : BaseAstNode
        {
            node.Parent = _currentNode;
            _currentNode.Children.Add(node);
            _currentNode = node;
        }

        private void TraverseUp()
        {
            _currentNode = _currentNode.Parent;
        }

        public override string ToString()
        {
            return PrintNode(_currentNode.GetSuperNode(), 0);
        }

        private string PrintNode(BaseAstNode node, int indent)
        {
            string output = "";


            for (var i = 0; i < indent; i++)
                output += "  ";

            if (indent != 0)
                output += "└─";
            output += node + Environment.NewLine;

            indent++;

            foreach (var child in node.Children)
            {
                output += PrintNode(child, indent);
            }

            return output;
        }
    }
}
