#include <stdio.h>
#include "ccl.h"
#include "cc_utils.h"

CCL_BUILD_LIST(char, String);


int main() {
    String name = String_from("Hello", 5);
    String sliced = String_slice(&name, 0, 4, 0);
    CCL_PRINTL("%c", sliced);
    return 0;
}