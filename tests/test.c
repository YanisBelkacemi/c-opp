#include <stdio.h>

#include "../headers/classes.h"

int main() {
    Class parent = Create_Class("Parent", NULL);
    Class child = Create_Class("Child", &parent);

    add_method(&parent, parent_hello, "hello");

    call_method(&child, "hello", NULL);

    add_method(&child, child_hello, "hello");

    call_method(&child, "hello", NULL);

    Destroy_class(&child);
    Destroy_class(&parent);
}