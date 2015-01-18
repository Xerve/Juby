#ifndef Prelude__Any_h
#define Prelude__Any_h

#include "Object.h"

void Prelude__Any__init(void);

Object* Prelude__Any__name(int argc, Object* argv[]);
Object* Prelude__Any__type(int argc, Object* argv[]);
Object* Prelude__Any__parent(int argc, Object* argv[]);
Object* Prelude__Any__is(int argc, Object* argv[]);
Object* Prelude__Any__in(int argc, Object* argv[]);

#endif
