using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UScript.Compiler.AST;
using UScript.Compiler.CompilerInterface.CodeGeneration.Structures;

namespace UScript.Compiler.CompilerInterface.CodeGeneration
{
    public interface ICodeGenerator
    {
        byte[] Code { get; }

        void BeginScope();
        void EndScope();
        IVariable DeclareVariable(string name);
        IVariable DeclareVariable(string name, UScriptDataType type);
        ILabel DefineLabel();
        void Emit(OpCode code);
        void Emit(OpCode code, string operand);
        void Emit(OpCode code, int operand);
        void Emit(OpCode code, IVariable operand);
        void EmitCall(IMemberReference target);
        void EmitMemberReference(IMemberReference @ref);
    }
}
