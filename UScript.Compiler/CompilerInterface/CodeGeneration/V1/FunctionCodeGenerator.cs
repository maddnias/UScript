using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using UScript.Compiler.Writer.Metadata.V1;

namespace UScript.Compiler.CompilerInterface.CodeGeneration.V1
{
    public class FunctionCodeGenerator : BasicCodeGenerator
    {
        public List<Parameter> Parameters => Scopes.First().Parameters;

        public FunctionCodeGenerator(IScriptCompilerContext context) 
            : base(context)
        {
        }

        public FunctionCodeGenerator(IScriptCompilerContext context, FunctionHeader funcHeader)
            : this(context)
        {
            var idx = 0;

            foreach (var param in funcHeader.Parameters)
            {
                Scopes.First().Parameters.Add(new Parameter
                {
                    Name = param.Name,
                    Type = param.Type,
                    Index = idx++
                });
            }
        }
    }
}
