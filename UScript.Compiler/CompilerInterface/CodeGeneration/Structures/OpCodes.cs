using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace UScript.Compiler.CompilerInterface.CodeGeneration.Structures
{
    public enum OpCode : byte
    {
        /// <summary>
        /// Saves data to a local variable
        /// </summary>
        SVAR,
        /// <summary>
        /// Loads data from a local variable
        /// </summary>
        LVAR,
        /// <summary>
        /// Saves data to a local variable and then loads it
        /// </summary>
        SLVAR,
        /// <summary>
        /// Adds two operands together
        /// </summary>
        ADD,
        /// <summary>
        /// Subtracts two operands
        /// </summary>
        SUB,
        /// <summary>
        /// Divides two operands
        /// </summary>
        DIV,
        /// <summary>
        /// Multiplies two operands
        /// </summary>
        MUL,
        /// <summary>
        /// Calls a function
        /// </summary>
        SCALL,
        /// <summary>
        /// Loads a string
        /// </summary>
        LSTR,
        /// <summary>
        /// Returns from a function
        /// </summary>
        RET,
        /// <summary>
        /// Loads an argument
        /// </summary>
        LPARAM,
        /// <summary>
        /// Loads an integer
        /// </summary>
        LINT
    }
}
