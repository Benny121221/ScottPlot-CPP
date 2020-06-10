using CommandLine;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Threading;

namespace CSharp_Wrapper_CLI
{
    class Program
    {
        class Options
        {
            [Option('x', Required = false, Separator = ' ')]
            public IEnumerable<double> xs { get; set; }

            [Option('y', Required = false, Separator = ' ')]
            public IEnumerable<double> ys { get; set; }

            [Option('o', "output", Required = true)]
            public string output { get; set; }
        }


        static void Main(string[] args)
        {
            ScottPlot.Plot plt = new ScottPlot.Plot();
            string plotType = args[0];

            Parser.Default.ParseArguments<Options>(args).WithParsed<Options>(o =>
            {
                switch (plotType.ToLower())
                {
                    case "scatter":
                        plt.PlotScatter(o.xs.ToArray(), o.ys.ToArray());
                        break;
                }

                plt.SaveFig(o.output);
            });
        }
    }
}
