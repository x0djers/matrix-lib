/**
  @file tests_runner.c
  @author x0djers
  @brief Модуль запуска всех тестов
*/

#include <CUnit/Basic.h>
#include <stdio.h>

void register_matrix_tests(void);
void register_output_tests(void);

int main() {
	CU_ErrorCode error;
	if (CU_initialize_registry() != CUE_SUCCESS) {
		error = CU_get_error();
	} else {
		register_matrix_tests();
		register_output_tests();

		CU_basic_set_mode(CU_BRM_VERBOSE);

		CU_basic_run_tests();

		CU_cleanup_registry();

		error = CU_get_error();
	}
	return error;
}