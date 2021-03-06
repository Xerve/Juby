#include "Object.h"
#include "ObjectNode.h"
#include "Scope.h"
#include "Interpreter.h"

#include "Prelude__Any.h"
#include "Prelude__Boolean.h"
#include "Prelude__Number.h"
#include "Prelude__Object.h"
#include "Prelude__Array.h"

Scope* Prelude(void);

void Prelude__init(void);

Object* Prelude__juby(int argc, Object* argv[]);
Object* Prelude__print(int argc, Object* argv[]);
Object* Prelude__let(int argc, Object* argv[]);
Object* Prelude__exit(int argc, Object* argv[]);
Object* Prelude__if(int argc, Object* argv[]);
