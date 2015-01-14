#ifndef Prelude__Any_h
#define Prelude__Any_h

#include "Object.h"

void Prelude__Any__init(void);

Object* Any__name(int argc, Object* argv[]);
Object* Any__type(int argc, Object* argv[]);
Object* Any__parent(int argc, Object* argv[]);

#endif
