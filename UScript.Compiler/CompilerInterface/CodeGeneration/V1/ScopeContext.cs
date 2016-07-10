using System.Collections.Generic;

namespace UScript.Compiler.CompilerInterface.CodeGeneration.V1
{
    public class ScopeContext
    {
        public List<Parameter> Parameters { get; set; }
        public List<LocalVariable> Variables { get; set; }

        public ScopeContext()
        {
            Parameters = new List<Parameter>();
            Variables = new List<LocalVariable>();
        }
    }
}