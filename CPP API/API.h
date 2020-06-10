#pragma once
#include <memory>
#include <string>

namespace ScottPlot {
	class __declspec(dllexport) PlotSettings {
	public:
		PlotSettings(int width = 800, int height = 600, bool showMarker = true, bool showLine = true);
		int width, height;
		bool showMarker, showLine;
	};

	__declspec(dllexport) void plot_scatter(double** xs, double** ys, char* output, int num_points[], int num_graphs, std::shared_ptr<PlotSettings> settings);
}
