# logress

This was an attempt to build a simple to use C++ logging framework for logging all calls at an API boundary.

The idea was that it would capture the instances, methods and arguments in a way that could then be played back as as a regression test.

It uses template metaprogramming to do compile time reflection of method arguments to (mostly) auto-generate the log parser.

In the end it proved too cumbersome to annotate the API boundary.

A lot of the implementation is based on ideas from Modern C++ Design
(http://www.amazon.ca/Modern-Design-Generic-Programming-Patterns/dp/0201704315)

Automatically exported from code.google.com/p/logress
