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

typedef struct _Tokens {
    int len;
    char* values[];
} Tokens;

Tokens* tokenize(char* input) {
    input++;
    int len = strlen(input) - 1;
    int num_tokens = 1;
    int point = 0;
    int token;
    bool in_str = false;
    int paren_level = 0;

    int i;
    for(i = 0; i < len; i++) {
        if (input[i] == ' ' && !in_str && paren_level == 0) {
            num_tokens++;
        } else if (input[i] == '\'') {
            if (i != 0) {
                if (input[i - 1] != '\\') {
                    in_str = !in_str;
                }
            } else {
                in_str = true;
            }
        } else if (input[i] == '(' && !in_str) {
            paren_level++;
        } else if (input[i] == ')' && !in_str) {
            paren_level--;
        }
        
        if (paren_level < 0) {
            puts("Unexpected ) !");
            exit(1);
        }
    }
    
    if (paren_level != 0) {
        puts("Number of () don't match!");
        exit(1);
    }
    
    if (in_str) {
        puts("Unended string!");
        exit(1);
    }
    
    int token_start[num_tokens];
    int token_len[num_tokens];
    
    token_start[0] = 0;
    for(i = 0; i < len; i++) {
        if (input[i] == ' ' && !in_str && paren_level == 0) {
            token_start[point + 1] = i + 1;
            token_len[point] = i - token_start[point];
            point++;
        } else if (input[i] == '\'') {
            if (i != 0) {
                if (input[i - 1] != '\\') {
                    in_str = !in_str;
                }
            } else {
                in_str = true;
            }
        } else if (input[i] == '(' && !in_str) {
            paren_level++;
        } else if (input[i] == ')' && !in_str) {
            paren_level++;
        }
    }
    token_len[num_tokens - 1] = len - token_start[num_tokens - 1];
    
    Tokens* ret = malloc(sizeof(Tokens) + (num_tokens * sizeof(char*)));
    ret->len = num_tokens;
    
    for (i = 0; i < num_tokens; i++) {
        ret->values[i] = substring(input, token_start[i] + 1, token_len[i]);
    }
    
    return ret;
}

void delete_Tokens(Tokens* tokens) {
    int i;
    for (i = 0; i < tokens->len; ++i) {
        free(tokens->values[i]);
    }
    
    free(tokens->values);
    free(tokens);
}

Object* eval(Object* context, char* in_string) {
    if (in_string[0] == '(' && in_string[strlen(in_string) - 1] == ')') {
        Tokens* tokens = tokenize(in_string);
        char** input = tokens->values;
        int len = tokens->len;
        
        int i;
        
        if (len == 0) {
            return undefined;
        }
        
        if (!strcmp(input[0], "undefined")) {
            return new_Undefined();
        }
        
        if (!strcmp(input[0], "get")) {
            if (len < 3) {
                puts("Invalid 'get':");
                printf("(");
                for (i = 0; i < len; i++) {
                    if (i != 0) {
                        printf(" ");
                    }
                    printf(input[i]);
                }
                puts(")");
                exit(1);
            } else {
                if (!strcmp(input[1], "_")) {
                    return get_Property(context, input[2]);
                } else {
                    return get_Property(eval(context, input[1]), input[2]);
                }
            }
        } else if (!strcmp(input[0], "set")) {
            if (len < 3) {
                puts("Invalid 'set':");
                printf("(");
                for (i = 0; i < len; i++) {
                    if (i != 0) {
                        printf(" ");
                    }
                    printf(input[i]);
                }
                puts(")");
                exit(1);
            } else {
                if (!strcmp(input[1], "_")) {
                    return set_Property(context, input[2], eval(context, input[3]));
                } else {
                    return set_Property(eval(context, input[1]), input[2], eval(context, input[3]));
                }
            }
        }
        
        delete_Tokens(tokens);
    } else {
        puts("Unknown wrapper!");
        exit(1);
    }
}