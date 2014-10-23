#include "juby.c"

int main() {
    Object* a = new_Object("m");
    set_Property(a, "P", new_String("ryan"));
    set_Property(a, "O", new_Integer(9));
    set_Property(a, "O", new_Integer(7));
    set_Property(a, "A", new_Integer(9));
    set_Property(a, "D", new_Integer(9));
    set_Property(a, "great!", new_Integer(9));
    set_Property(a, "B", new_Object("two"));
    set_Property(get_Property(a, "B"), "Y", new_String("YYY"));
    print_Object(eval(a, "(get _ B )"));
    //eval(a, "(set _ M (undefined))");
    print_Object(a);
    delete_Object(a);
    
    return 0;
}