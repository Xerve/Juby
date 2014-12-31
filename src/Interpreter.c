#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Interpreter.h"

char* substring(char* string, int position, int length) {
    char* pointer = malloc(length+1);

    int c;
    for (c = 0 ; c < position - 1 ; c++) {
        string++;
    }

    for (c = 0 ; c < length ; c++) {
        *(pointer+c) = *string;
        string++;
    }

    *(pointer+c) = '\0';

    return pointer;
}

Object* eval(Scope* scope, char* input) {
    if (!strcmp(input, "recover") || !strcmp(input, "(recover)")) {
          recover(true);
          return undefined;
    } else if (_panic) {
        return undefined;
    }

    int len = strlen(input);
    double num;

    if (input[0] == '(') {
        int i;
        int position = 0;
        int start = 0;
        int end = 0;
        int num_tokens = 0;
        bool in_str = false;
        int paren_level = 0;
        char last = '\0';

        for(i = 0; i < len; ++i) {
            if (paren_level >= 0) {
                if (!isNullChar(input[i]) && (isNullChar(last) || num_tokens == 0) && !in_str && paren_level == 1 && input[i] != ')') {
                    ++num_tokens;
                }

                if (input[i] == '\'') {
                    in_str = !in_str;
                } else if (input[i] == '(') {
                    ++paren_level;
                } else if (input[i] == ')') {
                    --paren_level;
                }

                last = input[i];
            }
        }

        if (paren_level > 0) {
            panic("Too many \"(\"!", NULL);
        } else if (paren_level < 0) {
            panic("Too many \")\"!", NULL);
        } else if (in_str) {
            panic("Too many \"'\"!", NULL);
        }

        in_str = false;
        paren_level = 0;
        char* tokens[num_tokens];
        for(i = 0; i < len; ++i) {
            if (paren_level >= 0) {
                if (!isNullChar(input[i]) && (isNullChar(last) || i == 1) && !in_str && paren_level == 1) {
                   start = i;
                }

                if (input[i] == '\'') {
                    in_str = !in_str;
                } else if (input[i] == '(') {
                    ++paren_level;
                } else if (input[i] == ')') {
                    --paren_level;
                }

                if (isNullChar(input[i]) && !isNullChar(last) && !in_str && paren_level == 1 && start != 0) {
                    end = i;
                } else if (paren_level == 0 && start != 0) {
                    end = i;
                }

                if (start != 0 && end != 0) {
                    tokens[position] = substring(input, start + 1, end - start);
                    ++position;
                    start = 0;
                    end = 0;
                }

                last = input[i];
            }
        }

        Object* ret = undefined;

        if (num_tokens == 0) {
            ret = undefined;
        } else if (!strcmp(tokens[0], "juby")) {
            for (i = 1; i < num_tokens; ++i) {
                ret = eval(scope, tokens[i]);
            }
        } else if (!strcmp(tokens[0], "panic")) {
            panic("User panic!", input);
        } else if (!strcmp(tokens[0], "print")) {
            if (num_tokens < 2) {
                panic("Invalid 'print':", input);
            } else {
                ret = print_Object(eval(scope, tokens[1]));
            }
        } else if (!strcmp(tokens[0], "new")) {
            if (num_tokens < 2) {
                panic("Invalid 'new':", input);
            } else {
                ret = new_Object(tokens[1]);
            }
        } else if (!strcmp(tokens[0], "delete")) {
            if (num_tokens < 2) {
                panic("Invalid 'delete':", input);
            } else {
                delete_Property(eval(scope, tokens[1]), tokens[2]);
            }
        } else if (!strcmp(tokens[0], "get")) {
            if (num_tokens < 3) {
                panic("Invalid 'get':", input);
            } else {
                ret = get_Property(eval(scope, tokens[1]), tokens[2]);
            }
        } else if (!strcmp(tokens[0], "set")) {
            if (num_tokens < 4) {
                panic("Invalid 'set':", input);
            } else {
                ret = set_Property(eval(scope, tokens[1]), tokens[2], eval(scope, tokens[3]));
            }
        } else {
            Object* args[num_tokens - 1];

            for(i = 1; i < num_tokens; ++i) {
                args[i - 1] = eval(scope, tokens[i]);
            }

            ret = apply_Object(scope, eval(scope, tokens[0]), args, num_tokens - 1);
        }

        for (i = 0; i < position; ++i) {
            free(tokens[i]);
        }

        return ret;
    } else if (input[0] == '\'' && input[len - 1] == '\'') {
        return new_String(substring(input, 2, len - 2));
    } else if (!strcmp(input, "true")) {
        return new_Boolean(true);
    } else if (!strcmp(input, "false")) {
        return new_Boolean(false);
    } else if (!strcmp(input, "undefined")) {
        return new_Undefined();
    } else if (num = strtold(input, NULL)) {
        return new_Number(num);
    } else if (input[0] == '0') {
        return new_Number(0.0);
    } else {
        return get_Variable(scope, input);
    }
}

Object* eval_lines(Scope* scope, char* input) {
    int len = strlen(input);
    double num;
    int i;
    int position = 0;
    int start = 0;
    int end = 0;
    int num_tokens = 0;
    bool in_str = false;
    int paren_level = 0;
    char last = '\0';

    for(i = 0; i < len; ++i) {
        if (paren_level >= 0) {
            if (!isNullChar(input[i]) && (isNullChar(last) || num_tokens == 0) && !in_str && paren_level == 1 && input[i] != ')') {
                ++num_tokens;
            }

            if (input[i] == '\'') {
                in_str = !in_str;
            } else if (input[i] == '(') {
                ++paren_level;
            } else if (input[i] == ')') {
                --paren_level;
            }

            last = input[i];
        }
    }

    if (paren_level > 0) {
        panic("Too many \"(\"!", NULL);
    } else if (paren_level < 0) {
        panic("Too many \")\"!", NULL);
    } else if (in_str) {
        panic("Too many \"'\"!", NULL);
    }

    in_str = false;
    paren_level = 0;
    char* tokens[num_tokens];
    for(i = 0; i < len; ++i) {
        if (paren_level >= 0) {
            if (!isNullChar(input[i]) && (isNullChar(last) || i == 1) && !in_str && paren_level == 1) {
                start = i;
            }

            if (input[i] == '\'') {
                in_str = !in_str;
            } else if (input[i] == '(') {
                ++paren_level;
            } else if (input[i] == ')') {
                --paren_level;
            }

            if (isNullChar(input[i]) && !isNullChar(last) && !in_str && paren_level == 1 && start != 0) {
                end = i;
            } else if (paren_level == 0 && start != 0) {
                end = i;
            }

            if (start != 0 && end != 0) {
                tokens[position] = substring(input, start + 1, end - start);
                ++position;
                start = 0;
                end = 0;
            }

            last = input[i];
        }
    }

    Object* ret = undefined;

    for (i = 0; i < num_tokens; ++i) {
        ret = eval(scope, tokens[i]);
    }

    for (i = 0; i < position; ++i) {
        free(tokens[i]);
    }

    return ret;
}
