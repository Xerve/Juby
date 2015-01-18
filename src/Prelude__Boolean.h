#ifndef Prelude__Boolean_h
#define Prelude__Boolean_h

#include "Object.h"

void Prelude__Boolean__init(void);

Object* Prelude__Boolean__and(int argc, Object* argv[]);
Object* Prelude__Boolean__or(int argc, Object* argv[]);
Object* Prelude__Boolean__xor(int argc, Object* argv[]);
Object* Prelude__Boolean__not(int argc, Object* argv[]);

#endif
