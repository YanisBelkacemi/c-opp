#include <stdio.h>

#include "../headers/classes.h"


void parent_hello(Class *self, void *args) {
    printf("Parent hello\n");
}

void child_hello(Class *self, void *args) {
    printf("Child hello\n");
}



int main() {
    Class* parent = Create_Class("Parent", NULL);
    Class* child = Create_Class("Child", parent);

    add_method(parent, parent_hello, "hello");

    call_method(child, "hello", NULL);

    add_method(child, child_hello, "hello");

    call_method(child, "hello", NULL);

    Destroy_class(child);
    Destroy_class(parent);
}