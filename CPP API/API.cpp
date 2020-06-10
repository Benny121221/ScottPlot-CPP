#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include "API.h"
#include <stdlib.h>
#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>

ScottPlot::PlotSettings settings = ScottPlot::PlotSettings(800, 600);

char* get_current_directory() {
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	return buffer;
}

void run_process(std::string pathargstr) {
	puts((pathargstr).c_str());
	system((pathargstr).c_str());
}


namespace ScottPlot {

	PlotSettings::PlotSettings(int width, int height, bool showMarker, bool showLine)
		: width(width), height(height), showMarker(showMarker), showLine(showLine)
	{

	}

	void plot_scatter(double** xs, double** ys, char* output, int num_points[], int num_graphs, std::shared_ptr<PlotSettings> settings)
	{
		char* directory = get_current_directory();
		for (int i = 0; i < 2; i++) {
			char* pos = directory;
			char* last_slash = pos;
			while (*pos) {
				if (*pos == '/' || *pos == '\\') {
					last_slash = pos;
				}
				pos += sizeof(char);
			}
			*last_slash = '\0';
		}

		char executable_path[MAX_PATH];
		puts(directory);
		strcpy_s(executable_path, directory);
		strcat_s(executable_path, "\\CSharp Wrapper CLI\\bin\\Release\\netcoreapp3.1\\CSharp Wrapper CLI.exe");

		std::unique_ptr<std::string> path_and_args = static_cast<std::unique_ptr<std::string>>(new std::string());
		*path_and_args += "\"";
		*path_and_args += executable_path;
		*path_and_args += "\" scatter -x \"";
		for (int i = 0; i < num_graphs; i++) {
			for (int j = 0; j < num_points[i]; j++) {
				*path_and_args += std::to_string(xs[i][j]) + " ";
			}
			if (i != num_graphs - 1) {
				*path_and_args += ",";
			}
		}

		*path_and_args += "\" -y \"";
		for (int i = 0; i < num_graphs; i++) {
			for (int j = 0; j < num_points[i]; j++) {
				*path_and_args += std::to_string(ys[i][j]) + " ";
			}
			if (i != num_graphs - 1) {
				*path_and_args += ",";
			}
		}

		*path_and_args += "\" -o \"";
		*path_and_args += output;
		*path_and_args += '\"';

		*path_and_args += " -w " + std::to_string(settings->width);
		*path_and_args += " -h " + std::to_string(settings->height);

		if (!settings->showLine) {
			*path_and_args += " --noDrawLine";
		}

		if (!settings->showMarker) {
			*path_and_args += " --noDrawMarkers";
		}
		
		*path_and_args = "start \"\" " + *path_and_args;

		std::cout << *path_and_args << std::endl;


		run_process(*path_and_args);
	}
}
