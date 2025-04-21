/**
  @file tests_output.c
  @author x0djers
  @brief Тесты для output.c
*/

#include <CUnit/Basic.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/output/output.h"

#define TEST_OUTPUT_FILE "test_output.txt"

void test_outputToStd(void) {
	const char* testStr = "Hello, stdout!\n";

	FILE* temp = tmpfile();
	CU_ASSERT_PTR_NOT_NULL(temp);

	outputToStd(testStr, temp);
	fflush(temp);

	rewind(temp);
	char buffer[256];
	fgets(buffer, sizeof(buffer), temp);

	CU_ASSERT_STRING_EQUAL(buffer, testStr);

	fclose(temp);
}

void test_outputToFile(void) {
	const char* testStr = "Hello, file!\n";

	outputToFile(testStr, TEST_OUTPUT_FILE);

	FILE* file = fopen(TEST_OUTPUT_FILE, "r");
	CU_ASSERT_PTR_NOT_NULL(file);

	char buffer[256];
	fgets(buffer, sizeof(buffer), file);

	CU_ASSERT_STRING_EQUAL(buffer, testStr);

	fclose(file);
	remove(TEST_OUTPUT_FILE);
}

void register_output_tests(void) {
	CU_pSuite suite = CU_add_suite("Output Tests", NULL, NULL);
	CU_add_test(suite, "Output to Std", test_outputToStd);
	CU_add_test(suite, "Output to File", test_outputToFile);
}
