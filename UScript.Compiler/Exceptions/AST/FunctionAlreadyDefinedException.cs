using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;

namespace UScript.Compiler.Exceptions.AST
{
    public class FunctionAlreadyDefinedException : AstException
    {
        public FunctionAlreadyDefinedException()
        {
        }

        public FunctionAlreadyDefinedException(string message) 
            : base(message)
        {
        }

        public FunctionAlreadyDefinedException(string message, Exception innerException) 
            : base(message, innerException)
        {
        }

        protected FunctionAlreadyDefinedException(SerializationInfo info, StreamingContext context) 
            : base(info, context)
        {
        }
    }
}
