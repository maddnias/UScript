using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using UScript.Compiler.AST;
using UScript.Compiler.CompilerInterface.CodeGeneration.Structures;
using UScript.Compiler.Tools.Extensions;
using UScript.Compiler.Writer.Metadata.V1;

namespace UScript.Compiler.CompilerInterface.CodeGeneration.V1
{
    public class BasicCodeGenerator : ICodeGenerator, IDisposable
    {
        private int _currentScope = 0;
        protected List<ScopeContext> Scopes { get; set; }
        private readonly IScriptCompilerContext _context;
        private readonly MemoryStream _code;

        public byte[] Code => _code.ToArray();

        public BasicCodeGenerator(IScriptCompilerContext context)
        {
            Scopes = new List<ScopeContext>
            {
                new ScopeContext
                {
                    Variables = new List<LocalVariable>(),
                    Parameters = new List<Parameter>()
                }
            };
            _code = new MemoryStream();
            _context = context;
        }

        public void BeginScope()
        {
            Scopes.Add(new ScopeContext());
            _currentScope++;
        }

        public void EndScope()
        {
            _currentScope--;
        }

        public IVariable DeclareVariable(string name)
        {
            Scopes[_currentScope].Variables.Add(new LocalVariable
            {
                Name = name,
                Index = Scopes[_currentScope].Variables.Count,
                Type = UScriptDataType.Undefined
            });

            return Scopes[_currentScope].Variables.Last();
        }

        public IVariable DeclareVariable(string name, UScriptDataType type)
        {
            Scopes[_currentScope].Variables.Add(new LocalVariable
            {
                Name = name,
                Index = Scopes[_currentScope].Variables.Count,
                Type = type
            });

            return Scopes[_currentScope].Variables.Last();
        }

        public ILabel DefineLabel()
        {
            throw new NotImplementedException();
        }

        public void Emit(OpCode code)
        {
            _code.WriteByte((byte)code);
        }

        public void Emit(OpCode code, string operand)
        {
            _code.WriteByte((byte) code);
            var strRef = new StringReference
            {
                MetadataToken = _context.StringTable.FirstOrDefault(x => x.Data == operand)?.Token
            };
            EmitMemberReference(strRef);
        }

        public void Emit(OpCode code, int operand)
        {
            _code.WriteByte((byte) code);
            _code.Write(BitConverter.GetBytes(operand), 0, sizeof(int));
        }

        public void Emit(OpCode code, IVariable operand)
        {
            _code.WriteByte((byte) code);
            _code.Write(BitConverter.GetBytes(operand.Index), 0, sizeof(int));
        }

        public void EmitCall(IMemberReference target)
        {
            _code.WriteByte((byte) OpCode.SCALL);
            _code.Write(BitConverter.GetBytes(target.MetadataToken.RawToken), 0, sizeof(int));
        }

        public void EmitMemberReference(IMemberReference @ref)
        {
            _code.Write(BitConverter.GetBytes(@ref.MetadataToken.RawToken), 0, sizeof(int));
        }

        public void Dispose()
        {
            _code.Dispose();
        }
    }
}
