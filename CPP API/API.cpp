#include "pch.h" // use stdafx.h in Visual Studio 2017 and earlier
#include "API.h"
#include <stdlib.h>
#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <vector>
#include <string>

#pragma warning(disable: 4996)

char* get_current_directory() {
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	return buffer;
}

void run_process(char* pathargstr) {
	system(pathargstr);
}

void plot_scatter(double* xs, double* ys, char* output, int num_points)
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

	int length = 500 + 11 * num_points * 2 + 2 * MAX_PATH;
	char* path_and_args = (char*)calloc(length, sizeof(char));
	path_and_args[0] = '"';
	strcat(path_and_args, executable_path);
	strcat(path_and_args, "\" scatter -x ");
	for (int i = 0; i < num_points; i++) {
		strcat(path_and_args, (char*)std::to_string(xs[i]).c_str());
		strcat(path_and_args, " ");
	}

	strcat(path_and_args, "-y ");
	for (int i = 0; i < num_points; i++) {
		strcat(path_and_args, (char*)std::to_string(ys[i]).c_str());
		strcat(path_and_args, " ");
	}

	strcat(path_and_args, "-o ");
	strcat(path_and_args, output);


	run_process(path_and_args);
	free(path_and_args);
}
