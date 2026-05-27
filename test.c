#include <stdio.h>
#include <string.h>
#include "include/ccl.h"
#include "include/cc_utils.h"
#include "include/cc_string.h"

CCS_BUILD_STRING()
CCS_BUILD_UTILS()


int main() {
    String name = String_FromCstr("Daniel Alonso");
    name = String_ToLowerCase(&name);
    String hint = String_FromCstr("lonso");
    if (String_EndsWith(&name, &hint)) {
        printf("Hello Daniel");
    }
    String_print(&name, '\n');
    printf("%s\n", String_ToCstr(&name));
    return 0;
}