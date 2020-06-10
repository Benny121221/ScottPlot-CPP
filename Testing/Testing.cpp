#include <iostream>
#include "../CPP API/API.h"

int main()
{
    std::shared_ptr<ScottPlot::PlotSettings> settings = std::shared_ptr<ScottPlot::PlotSettings>(new ScottPlot::PlotSettings(200));
    ScottPlot::plot_scatter(new double[3] {1, 5, 10}, new double[3] {2,3,2}, (char*) "C:/Users/benny/Desktop/b.png", 3, settings);
}
