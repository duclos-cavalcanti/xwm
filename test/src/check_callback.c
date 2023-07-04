#include "test.h"

START_TEST(CASE_1) {
    ck_assert_int_eq(2+4, 6);
}

Suite* callback(void) {
    Suite* s = suite_create("Suite Callbacks");
    TCase* tcase = tcase_create("Case 0");

    tcase_add_test(tcase, CASE_1);
    suite_add_tcase(s, tcase);

    return s;
}

