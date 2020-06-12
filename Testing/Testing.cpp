#include <iostream>
#include "../CPP API/API.h"

int main()
{
    std::shared_ptr<ScottPlot::PlotSettings> settings = std::shared_ptr<ScottPlot::PlotSettings>(new ScottPlot::PlotSettings());
    /*double** xs = new double* [2];
    double** ys = new double* [2];
    xs[0] = new double[3]{ 1, 5, 10 };
    xs[1] = new double[3]{ 2, 8 };
    ys[0] = new double[3]{ 2, 3, 2 };
    ys[1] = new double[3]{ 1, 2 };
    ScottPlot::plot_scatter(xs, ys, (char*)"C:/Users/benny/Desktop/b.png", new int[2]{ 3, 2 }, 2, settings);*/

    double** ys = new double* [2];
    ys[0] = new double[3]{ 2, 3, 2 };
    ys[1] = new double[3]{ 1, 2 };
    std::string labels[2] = {"ha", "ba"};
    ScottPlot::plot_signal(ys, new double[2]{ 2, 1 }, new double[2]{ 1, 1.1 }, (char*)"C:/Users/benny/Desktop/b.png", new int[2]{ 3, 2 }, 2, settings, labels);

}
