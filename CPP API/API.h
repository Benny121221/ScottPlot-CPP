#pragma once
#include <memory>
#include <string>

namespace ScottPlot {
	class __declspec(dllexport) PlotSettings {
	public:
		PlotSettings(int width = 800, int height = 600);
		int width, height;
	};

	__declspec(dllexport) void plot_scatter(double xs[], double ys[], char* output, int num_points, std::shared_ptr<PlotSettings> settings);
}
