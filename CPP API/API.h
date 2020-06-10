#pragma once
#include <memory>
#include <string>

__declspec(dllexport) extern void plot_scatter(double xs[], double ys[], char* output, int num_points);
__declspec(dllexport) extern void plot_scatter(double xs[], double ys[], std::string* output, int num_points);
__declspec(dllexport) extern void set_dimensions(int width, int height);
