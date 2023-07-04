#include "test.h"

START_TEST(CASE_0) {
    ck_assert_int_eq(2+2, 4);
}

Suite* linked_list(void) {
    Suite* s = suite_create("Suite Linked List");
    TCase* tcase = tcase_create("Case 0");

    tcase_add_test(tcase, CASE_0);
    suite_add_tcase(s, tcase);

    return s;
}

