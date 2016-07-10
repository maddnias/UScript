using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using UScript.Compiler.CompilerInterface;
using UScript.Compiler.CompilerInterface.Compilers;

namespace UScript.CompilerUI
{
    class Program
    {
        static void Main(string[] args)
        {
            var compiler = ScriptCompilerFactory.CreateCompiler(new Version(1, 0));
            compiler.Compile(new SourceFile("C:\\script.usc"));


            Console.ReadLine();
        }
    }
}
