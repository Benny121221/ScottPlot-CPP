#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include "API.h"
#include <stdlib.h>
#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <string>

ScottPlot::PlotSettings settings = ScottPlot::PlotSettings(800, 600);

char* get_current_directory() {
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	return buffer;
}

void run_process(char* pathargstr) {
	system(pathargstr);
}


namespace ScottPlot {

	PlotSettings::PlotSettings(int width, int height)
	{
		this->width = width;
		this->height = height;
	}


	void plot_scatter(double xs[], double ys[], char* output, int num_points, std::shared_ptr<PlotSettings> settings)
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
		strcpy_s(executable_path, directory);
		strcat_s(executable_path, "/CSharp Wrapper CLI/bin/Release/netcoreapp3.1/CSharp Wrapper CLI.exe");

		std::unique_ptr<std::string> path_and_args = static_cast<std::unique_ptr<std::string>>(new std::string());
		*path_and_args += '"';
		*path_and_args += executable_path;
		*path_and_args += "\" scatter -x ";
		for (int i = 0; i < num_points; i++) {
			*path_and_args += std::to_string(xs[i]) + " ";
		}

		*path_and_args += "-y ";
		for (int i = 0; i < num_points; i++) {
			*path_and_args += std::to_string(ys[i]) + " ";
		}

		*path_and_args += "-o ";
		*path_and_args += output;

		*path_and_args += " -w " + std::to_string(settings->width);
		*path_and_args += " -h " + std::to_string(settings->height);


		run_process((char*)path_and_args->c_str());
	}
}
