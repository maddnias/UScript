using System;
using System.Runtime.Serialization;

namespace UScript.Compiler.Exceptions.AST
{
    public class AstException : Exception
    {
        public AstException()
        {
        }

        public AstException(string message) 
            : base(message)
        {
        }

        public AstException(string message, Exception innerException) 
            : base(message, innerException)
        {
        }

        protected AstException(SerializationInfo info, StreamingContext context) 
            : base(info, context)
        {
        }
    }
}
