using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using LibSassNet;
using System.Threading.Tasks;

namespace libsasstest
{
    class Program
    {
        static string OutputDir = "test_output";

        static void Main(string[] args)
        {
            if ( !Directory.Exists(OutputDir) )
            {
                Directory.CreateDirectory(OutputDir);
            }

            List<int> jobList = new List<int> { 1 };//, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30 };

            var sw = new Stopwatch();
            sw.Start();
            
            //jobList.ForEach(jobID => Process(jobID)); // <== Sequencial 
            Parallel.ForEach(jobList, jobID => Process(jobID)); // <== Multithreaded / Parallel

            sw.Stop();
            Console.WriteLine("Total time: {0}.", sw.ElapsedMilliseconds);

            //Console.ReadLine();
        }

        static void Process(int jobID )
        {
            Console.WriteLine("Start JobID: {0}...", jobID);

            var sw = new Stopwatch();
            sw.Start();

            SassCompiler compiler = new SassCompiler();
            {

                //var result = compiler.CompileFile(Path.Combine(srcpath, @"..\..\bootstrap.scss"), includeSourceComments: false );
                var result = compiler.CompileFile(@"default.scss", OutputStyle.Nested, "http://winfly/", false, 5, true, null);

                File.WriteAllText(String.Format(@"{0}\foundation-libsass{1}.css", OutputDir, jobID), result.CSS);
            }

            sw.Stop();
            Console.WriteLine("JobID: {0} Took: {1}.", jobID, sw.ElapsedMilliseconds);   
        }
    }
}
