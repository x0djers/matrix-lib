#include "output.h"

void outputToStdOut(const char *buffer) {
	puts(buffer);
}

void outputToFile(const char *buffer, FILE *file) {
	fputs(buffer, file);
}