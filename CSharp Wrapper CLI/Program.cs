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
		[Verb("scatter", HelpText = "Scatter Plot")]
		class ScatterOptions : GenericOptions
		{
			[Option('x', Required = true)]
			public string xs { get; set; }

			[Option('y', Required = true)]
			public string ys { get; set; }
		}

		[Verb("signal", HelpText = "Signal Plot")]
		class SignalOptions : GenericOptions
		{
			[Option('y', Required = true)]
			public string ys { get; set; }

			[Option("sampleRates", Required = true, Separator = ',')]
			public IEnumerable<double> sampleRates { get; set; }

			[Option("offsets", Required = true, Separator = ',')]
			public IEnumerable<double> offsets { get; set; }
		}

		class GenericOptions
		{
			[Option('o', "output", Required = true)]
			public string output { get; set; }

			[Option('w', "width", Required = false, Default = 800)]
			public int width { get; set; }

			[Option('h', "height", Required = false, Default = 600)]
			public int height { get; set; }

			[Option("noDrawLine", Required = false, Default = false)]
			public bool noDrawLine { get; set; }

			[Option("noDrawMarkers", Required = false, Default = false)]
			public bool noDrawMarkers { get; set; }

			[Option('n', "names", Required = false, Separator = ',')]
			public IEnumerable<string> names { get; set; }

		}


		static void Main(string[] args)
		{
			//foreach (string curr in args) {
			//	Console.WriteLine(curr);
			//}
			//string x = Console.ReadLine();
			Parser.Default.ParseArguments<ScatterOptions, SignalOptions>(args)
				.WithParsed<ScatterOptions>(o =>
				{
					ScottPlot.Plot plt = new ScottPlot.Plot(o.width, o.height);
					string[] xs_array = o.xs.Split(',').Select(s => s.Trim()).ToArray();
					string[] ys_array = o.ys.Split(',').Select(s => s.Trim()).ToArray();
					string[] label_array = null;
					if (o.names != null) {
						label_array = o.names.ToArray();
					}

					for (int i = 0; i < xs_array.Length; i++)
					{
						string[] curr_xs_str = xs_array[i].Split(' ');
						string[] curr_ys_str = ys_array[i].Split(' ');
						double[] curr_xs = curr_xs_str.Select(s => double.Parse(s)).ToArray();
						double[] curr_ys = curr_ys_str.Select(s => double.Parse(s)).ToArray();
						plt.PlotScatter(curr_xs, curr_ys, lineWidth: !o.noDrawLine ? 1 : 0, markerSize: !o.noDrawMarkers ? 5 : 0, label: label_array != null ? label_array[i] : null);
					}

					if (o.names != null)
					{
						plt.Legend();
					}

					plt.SaveFig(o.output);
				}).WithParsed<SignalOptions>(o =>
				{
					ScottPlot.Plot plt = new ScottPlot.Plot(o.width, o.height);
					string[] ys_array = o.ys.Split(',').Select(s => s.Trim()).ToArray();
					double[] sampleRatesArray = o.sampleRates.ToArray();
					double[] offsetsArray = o.offsets.ToArray();
					string[] label_array = null;
					if (o.names != null)
					{
						label_array = o.names.ToArray();
					}

					for (int i = 0; i < ys_array.Length; i++)
					{
						string[] curr_ys_str = ys_array[i].Split(' ');
						double[] curr_ys = curr_ys_str.Select(s => double.Parse(s)).ToArray();
						plt.PlotSignal(curr_ys, sampleRatesArray[i], offsetsArray[i], lineWidth: !o.noDrawLine ? 1 : 0, markerSize: !o.noDrawMarkers ? 5 : 0, label: label_array != null ? label_array[i] : null);
					}

					if (o.names != null)
					{
						plt.Legend();
					}

					plt.SaveFig(o.output);
				});
		}
	}
}
