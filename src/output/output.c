#include "output.h"

#include <stdio.h>

void outputToStd(const char* buffer, void* context) {
	fputs(buffer, context);
}

void outputToFile(const char* buffer, void* context) {
	const char* fileName = context;
	FILE* file = fopen(fileName, "w");
	fputs(buffer, file);
}