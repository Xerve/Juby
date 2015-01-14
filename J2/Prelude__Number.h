#ifndef Prelude__Number_h
#define Prelude__Number_h

#include "Object.h"

void Prelude__Number__init(void);

Object* Number__add(int argc, Object* argv[]);
Object* Number__sub(int argc, Object* argv[]);
Object* Number__mul(int argc, Object* argv[]);
Object* Number__div(int argc, Object* argv[]);

#endif
