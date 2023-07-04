#include "test.h"
#include "main.h"

window_manager_t *wm = { 0 };

extern Suite* linked_list(void); 
extern Suite* callback(void); 

int main(void) {
    Suite *s;
    SRunner *sr = srunner_create(NULL);
    Suite* suites[] = {
        linked_list(), 
        callback()
    };


    for (size_t i = 0; i < (sizeof(suites)/sizeof(suites[0])); i++) {
        s = suites[i];
       srunner_add_suite(sr, s);
    }

    srunner_run_all(sr, CK_NORMAL);
    int failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return (failed == 0) ? 0 : 1;
}
