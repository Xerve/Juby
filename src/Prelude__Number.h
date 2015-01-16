#ifndef Prelude__Number_h
#define Prelude__Number_h

#include "Object.h"

void Prelude__Number__init(void);

Object* Prelude__Number__add(int argc, Object* argv[]);
Object* Prelude__Number__sub(int argc, Object* argv[]);
Object* Prelude__Number__mul(int argc, Object* argv[]);
Object* Prelude__Number__div(int argc, Object* argv[]);

#endif
