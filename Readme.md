# C-OPP

A small OOP system written in C.

I started this project because I wanted to understand how some of the features we normally associate with object-oriented languages can be implemented in C.

There is no magic here. Classes, methods, inheritance and polymorphism are built using structs, function pointers, hash tables and dynamic memory.

The project is still being developed, so the API and internal design may change.

## What it currently supports

* Classes
* Methods
* Method lookup using a hash table
* Inheritance
* Method overriding
* `self` pointer
* Opaque `Class` type
* Dynamic allocation of classes and methods
* Method arguments through `void *`

A simple inheritance structure currently looks like:

```text
Parent
  |
  v
Child
```

When calling a method on `Child`, the library searches the child first and then walks up the parent chain if the method isn't found.

## Example

Creating classes:

```c
Class *parent = Create_Class("Parent", NULL);
Class *child = Create_Class("Child", parent);
```

Adding a method:

```c
void parent_hello(Class *self, void *args)
{
    printf("Hello parent");
}

add_method(parent_hello, hello, "hello");
```

Calling it:

```c
call_method(child, "hello", NULL);
```

Since `Child` inherits from `Parent`, the method defined in `Parent` can be found and executed on the `Child`.

## How it works

The main structure is currently:

```c
struct Class {
    char *name;
    Method **bucket;
    size_t capacity;
    Class *parent;
};
```

Methods are stored in a hash table:

```text
Class
 |
 +-- bucket[0] -> Method -> Method
 |
 +-- bucket[1]
 |
 +-- bucket[2] -> Method
 |
 +-- ...
 |
 +-- parent
```

Method names are hashed to determine which bucket they belong to.

If a method isn't found in the current class, the library checks the parent class:

```text
Child
  |
  | method not found
  v
Parent
  |
  | method not found
  v
Grandparent
```

This also gives method overriding naturally. If both the child and parent have a method with the same name, the child's method is found first.

## Why I made this

I'm mainly using this project to learn more about C rather than trying to create a replacement for C++.

The interesting part for me is understanding what is actually happening underneath features like:

* objects
* inheritance
* polymorphism
* dynamic dispatch
* method tables
* memory management

C gives you enough low-level control to build these things yourself, but it also makes you deal with the design decisions that higher-level languages hide.

## Future plans

The project is still fairly early, and I want to expand it gradually.

### Object system

* [ ] Add an `Object` / instance system
* [ ] Add instance-specific data
* [ ] Allow multiple objects to be created from the same class
* [ ] Add constructors
* [ ] Add destructors

### Inheritance and polymorphism

* [ ] Improve runtime type checking
* [ ] Add a way to call a parent's implementation of an overridden method
* [ ] Add class/type IDs
* [ ] Experiment with interfaces or abstract classes
* [ ] Experiment with virtual method tables

### Method system

* [ ] Add method removal
* [ ] Add `has_method()`
* [ ] Improve method lookup
* [ ] Improve method argument handling
* [ ] Add support for class/static methods

### Memory and reliability

* [ ] Handle allocation failures
* [ ] Add better `NULL` checking
* [ ] Define clear ownership rules
* [ ] Add dynamic resizing to the method hash table
* [ ] Improve cleanup and error handling

### Project quality

* [ ] Add a proper test suite
* [ ] Add examples
* [ ] Improve API documentation
* [ ] Improve project structure
* [ ] Make the library easier to integrate into other C projects

## Project structure

```text
c-opp/
├── headers/
│   └── classes.h
├── source/
│   └── classes.c
├── tests/
│   └── test.c
└── README.md
```

## Building

Using GCC:

```bash
gcc -o test tests/test.c source/classes.c
```

Run:

```bash
./test
```

On Windows:

```bash
test.exe
```

## Status

This is a learning project and is **not production-ready**.

The API and internal implementation will probably change as I add features and find better ways to structure the library.

The goal isn't to recreate C++ in C.

The goal is to understand how these concepts actually work underneath the abstraction.
