#ifndef Prelude__Array_h
#define Prelude__Array_h

#include "Object.h"

void Prelude__Array__init(void);

Object* Prelude__Array__Array(int argc, Object* argv[]);
Object* Prelude__Array__get(int argc, Object* argv[]);
Object* Prelude__Array__push(int argc, Object* argv[]);
Object* Array__pop(int argc, Object* argv[]);
Object* Array__print(int argc, Object* argv[]);

#endif
