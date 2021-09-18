#include "SimpleString.h"

int main() {
    SimpleString str{ 50 };
    str.append_line("Something something");
    str.append_line("dark size");
    str.print("str");
    
    str *= 3;
    str.print("str after mult(3)");
}
