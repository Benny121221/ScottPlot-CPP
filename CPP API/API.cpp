#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include "API.h"
#include <stdlib.h>
#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <string>

int plot_width = 800;
int plot_height = 600;

char* get_current_directory() {
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	return buffer;
}

void run_process(char* pathargstr) {
	system(pathargstr);
}

void plot_scatter(double xs[], double ys[], std::string* output, int num_points)
{
	plot_scatter(xs, ys, (char*)output->c_str(), num_points);
}

void set_dimensions(int width, int height)
{
	plot_width = width;
	plot_height = height;
}

void plot_scatter(double xs[], double ys[], char* output, int num_points)
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

	*path_and_args += " -w " + std::to_string(plot_width);
	*path_and_args += " -h " + std::to_string(plot_height);


	run_process((char*)path_and_args->c_str());
}
