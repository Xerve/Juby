#include "Object.h"
#include "ObjectNode.h"
#include "Scope.h"
#include "Interpreter.h"

#include "Prelude__Any.h"
#include "Prelude__Number.h"

Scope* Prelude(void);

void Prelude__init(void);

Object* Prelude__juby(int argc, Object* argv[]);
Object* Prelude__print(int argc, Object* argv[]);
Object* Prelude__let(int argc, Object* argv[]);
Object* Prelude__quit(int argc, Object* argv[]);
