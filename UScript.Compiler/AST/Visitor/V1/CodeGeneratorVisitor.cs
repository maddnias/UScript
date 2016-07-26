using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UScript.Compiler.CompilerInterface;
using UScript.Compiler.CompilerInterface.CodeGeneration;
using UScript.Compiler.CompilerInterface.CodeGeneration.Structures;
using UScript.Compiler.CompilerInterface.CodeGeneration.V1;
using UScript.Compiler.Writer.Metadata.V1;

namespace UScript.Compiler.AST.Visitor.V1
{
    public class CodeGeneratorVisitor : AstVisitor
    {
        private readonly IScriptCompilerContext _context;
        private readonly FunctionHeader _funcHeader;

        public CodeGeneratorVisitor(IScriptCompilerContext context)
        {
            _context = context;
        }

        public CodeGeneratorVisitor(IScriptCompilerContext context, FunctionHeader funcHeader)
        {
            _context = context;
            _funcHeader = funcHeader;
            _funcHeader.CodeGen = new FunctionCodeGenerator(context, funcHeader);
        }

        public override void VisitArgumentDeclarationNode(ArgumentDeclarationNode node)
        {
            node.Exp.Accept(this);
        }

        public override void VisitArgumentListNode(ArgumentListNode node)
        {

        }

        public override void VisitArithmeticExpressionNode(ArithmeticExpressionNode node)
        {
            node.Children.First().Accept(this);
            node.Children.Last().Accept(this);

            foreach (var expNode in node.Children)
                ExceptionNodes.Add(expNode);

            switch (node.Op)
            {
                case ArithmeticOp.Add:
                    if (_funcHeader != null)
                        _funcHeader.CodeGen.Emit(OpCode.ADD);
                    else
                        _context.CodeGen.Emit(OpCode.ADD);
                    break;
                case ArithmeticOp.Subtract:
                    if (_funcHeader != null)
                        _funcHeader.CodeGen.Emit(OpCode.SUB);
                    else
                        _context.CodeGen.Emit(OpCode.SUB);
                    break;
                case ArithmeticOp.Mul:
                    if (_funcHeader != null)
                        _funcHeader.CodeGen.Emit(OpCode.MUL);
                    else
                        _context.CodeGen.Emit(OpCode.MUL);
                    break;
                default:
                    throw new ArgumentOutOfRangeException();
            }
        }

        public override void VisitExpressionNode(ExpressionNode node)
        {
            return;
        }

        public override void VisitFunctionCallStatementNode(FunctionCallStatementNode node)
        {
            var argList = node.Children.First(x => x is ArgumentListNode);
            var args = argList.Children.Reverse().ToList();

            // Push arguments
            foreach (var argNode in args)
                argNode.Accept(this);

            // Don't visit these afterwards
            args.ForEach(x => ExceptionNodes.Add(x));
            ExceptionNodes.Add(argList);

            if (_funcHeader != null)
                _funcHeader.CodeGen.EmitCall(new FunctionReference
                {
                    MetadataToken = _context.FunctionTable.First(x => x.Name == node.FunctionName).Token
                });
            else
                _context.CodeGen.EmitCall(new FunctionReference
                {
                    MetadataToken = _context.FunctionTable.First(x => x.Name == node.FunctionName).Token
                });
        }

        public override void VisitFunctionDeclarationNode(FunctionDeclarationNode node)
        {
            foreach (var child in node.Children)
                child.Accept(this);
        }

        public override void VisitParameterDeclarationNode(ParameterDeclarationNode node)
        {
        }

        public override void VisitParameterListNode(ParameterListNode node)
        {
        }

        public override void VisitReturnStatementNode(ReturnStatementNode node)
        {
            if (node.Children.FirstOrDefault() != null)
            {
                node.Children.First().Accept(this);
                ExceptionNodes.Add(node.Children.First());
            }

            if (_funcHeader != null)
                _funcHeader.CodeGen.Emit(OpCode.RET);
            else
                _context.CodeGen.Emit(OpCode.RET);
        }

        public override void VisitVariableDeclarationNode(VariableDeclarationNode node)
        {
            IVariable variable;

            if (_funcHeader != null)
                variable = _funcHeader.CodeGen.DeclareVariable(node.Name);
            else
                variable = _context.CodeGen.DeclareVariable(node.Name);

            node.Children.First().Accept(this);

            ExceptionNodes.Add(node.Children.First());

            if (_funcHeader != null)
                _funcHeader.CodeGen.Emit(OpCode.SLVAR, variable);
            else
                _context.CodeGen.Emit(OpCode.SLVAR, variable);
        }

        public override void VisitStringNode(StringNode node)
        {
        }

        public override void VisitNumberExpressionNode(NumberExpressionNode node)
        {
            var num = int.Parse(node.Context.GetText());
            if (_funcHeader != null)
                _funcHeader.CodeGen.Emit(OpCode.LI32, num);
            else
                _context.CodeGen.Emit(OpCode.LI32, num);
        }

        public override void VisitVariableReferenceNode(VariableReferenceNode node)
        {
            IVariable referencedVariable = null;

            if (_funcHeader != null)
                referencedVariable = _funcHeader.CodeGen.Parameters.FirstOrDefault(x => x.Name == node.Name);

            if (_funcHeader != null)
                _funcHeader.CodeGen.Emit(OpCode.LPARAM, _funcHeader.CodeGen.Parameters.First(x => x.Name == node.Name));
        }
    }
}
