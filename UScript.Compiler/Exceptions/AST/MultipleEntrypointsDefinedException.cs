using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.Serialization;
using System.Text;

namespace UScript.Compiler.Exceptions.AST
{
    public class MultipleEntrypointsDefinedException : AstException
    {
        public MultipleEntrypointsDefinedException()
        {
        }

        public MultipleEntrypointsDefinedException(string message) 
            : base(message)
        {
        }

        public MultipleEntrypointsDefinedException(string message, Exception innerException) 
            : base(message, innerException)
        {
        }

        protected MultipleEntrypointsDefinedException(SerializationInfo info, StreamingContext context) 
            : base(info, context)
        {
        }
    }
}
