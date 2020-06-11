#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include "API.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>

#define MAXPATHSIZE ((rsize_t)MAX_PATH)

ScottPlot::PlotSettings settings = ScottPlot::PlotSettings(800, 600);

char* get_current_directory() {
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	return buffer;
}

void run_process(std::string pathargstr) {
#if defined _WIN32 || defined _WIN64
	pathargstr = "start \"\" " + pathargstr;
#else
	pathargstr = ". " + pathargstr
#endif
	
	system((pathargstr).c_str());
}

namespace ScottPlot {

	PlotSettings::PlotSettings(int width, int height, bool showMarker, bool showLine)
		: width(width), height(height), showMarker(showMarker), showLine(showLine)
	{

	}

	void append_generic_options(std::shared_ptr<std::string> argstr, std::shared_ptr<ScottPlot::PlotSettings> settings) {
		*argstr += " -w " + std::to_string(settings->width);
		*argstr += " -h " + std::to_string(settings->height);

		if (!settings->showLine) {
			*argstr += " --noDrawLine";
		}

		if (!settings->showMarker) {
			*argstr += " --noDrawMarkers";
		}
	}

	void get_wrapper_path(char buffer[MAX_PATH]) {
		char* directory = get_current_directory();
		for (int i = 0; i < 3; i++) {
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

		strcpy_s(buffer, MAXPATHSIZE, directory);
		strcat_s(buffer, MAXPATHSIZE, "\\CSharp Wrapper CLI\\bin\\Release\\netcoreapp3.1\\CSharp Wrapper CLI.exe");
	}

	void plot_scatter(double** xs, double** ys, char* output, int num_points[], int num_graphs, std::shared_ptr<PlotSettings> settings)
	{
		char executable_path[MAX_PATH];
		get_wrapper_path(executable_path);

		std::shared_ptr<std::string> path_and_args = static_cast<std::shared_ptr<std::string>>(new std::string());
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

		puts(path_and_args->c_str());

		ScottPlot::append_generic_options(path_and_args, settings);

		run_process(*path_and_args);
	}

	void plot_signal(double** ys, double sampleRates[], double offsets[], char* output, int num_points[], int num_graphs, std::shared_ptr<PlotSettings> settings)
	{
		char executable_path[MAX_PATH];
		get_wrapper_path(executable_path);

		std::shared_ptr<std::string> path_and_args = static_cast<std::shared_ptr<std::string>>(new std::string());
		*path_and_args += "\"";
		*path_and_args += executable_path;
		*path_and_args += "\" signal -y \"";
		for (int i = 0; i < num_graphs; i++) {
			for (int j = 0; j < num_points[i]; j++) {
				*path_and_args += std::to_string(ys[i][j]) + " ";
			}
			if (i != num_graphs - 1) {
				*path_and_args += ",";
			}
		}

		*path_and_args += "\" --sampleRates ";
		for (int i = 0; i < num_graphs; i++) {
			*path_and_args += std::to_string(sampleRates[i]); 
			if (i != num_graphs - 1) {
				*path_and_args += ",";
			}
		}

		*path_and_args += " --offsets ";
		for (int i = 0; i < num_graphs; i++) {
			*path_and_args += std::to_string(offsets[i]);
			if (i != num_graphs - 1) {
				*path_and_args += ",";
			}
		}

		*path_and_args += " -o \"";
		*path_and_args += output;
		*path_and_args += '\"';

		ScottPlot::append_generic_options(path_and_args, settings);

		run_process(*path_and_args);
	}


}
