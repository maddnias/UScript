using System;
using System.Collections.Generic;
using System.IO;
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
            var test = compiler.Compile(new SourceFile("C:\\script.usc"));


            File.WriteAllBytes("C:\\Users\\mattias\\Documents\\compiled_script.usce", test.CompiledPE);

            Console.ReadLine();
        }
    }
}
