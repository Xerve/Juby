# Juby

A programming language

## Y Lisp

Y Lisp is the language of the Juby runtime, which is what Juby gets
compiled down into. Examples of it can be seen in the examples directory.

## Building

Building is veryyyyyyyyyyyyyyyyyyyy easy. `gcc *.c -o juby` is all it takes.
You can then invoke a REPL session.

Alternatively, you can run a file the the `-y` flag, so for example

    ./juby.out -y examples/person.y

## TODO

[X] Object system

[X] eval

[X] Interpretter

[X] Run files

[ ] Copy objects

[ ] Object literals

[ ] Arrays and array literals

[X] Function objects

[ ] Function literals

[ ] Garbage collector

[X] User CLI input

[ ] Read from files
