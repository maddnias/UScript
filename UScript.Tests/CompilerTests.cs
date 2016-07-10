using System;
using System.IO;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using UScript.Compiler.CompilerInterface;
using UScript.Compiler.CompilerInterface.Compilers;

namespace UScript.Tests
{
    [TestClass]
    public class CompilerTests
    {
        [TestMethod]
        public void CompileBasic()
        {
            var compiler = ScriptCompilerFactory.CreateCompiler(new Version(1, 0));

            var result = compiler.Compile(new SourceFile("C:\\script.usc"));

            Assert.IsTrue(result.CompiledPE.Length > 0);
            Assert.AreEqual(result.Errors.Count, 0);
        }
    }
}
