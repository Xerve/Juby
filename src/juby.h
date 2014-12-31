#include "utils.h"
#include "Object.h"
#include "Node.h"
#include "Scope.h"
#include "Interpreter.h"

#define PreludeFunc(name) set_Property(p, #name, new_nFunction(name));

Scope* Prelude(void);
