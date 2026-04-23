#include <check.h>
#include <stdlib.h>

Suite *sum_suite(void);
Suite *create_suite(void);
Suite *sub_suite(void);
Suite *mult_number(void);
Suite *mult_matrix(void);
Suite *transpose_suite(void);
Suite *complements_suite(void);
Suite *test_inverse(void);

int main(void) {
  int number_failed;
  SRunner *sr;
  sr = srunner_create(sum_suite());
  srunner_add_suite(sr, create_suite());
  srunner_add_suite(sr, sub_suite());
  srunner_add_suite(sr, mult_number());
  srunner_add_suite(sr, mult_matrix());
  srunner_add_suite(sr, transpose_suite());
  srunner_add_suite(sr, complements_suite());
  srunner_add_suite(sr, test_inverse());

  srunner_run_all(sr, CK_NORMAL);

  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}