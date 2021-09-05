#include "SimpleString.h"
#include <utility>

int main() {
    SimpleString str{ 50 };
    str.append_line("Something something");
    str.append_line("dark size");
    
    SimpleString str_copy{ str };
    str.print("[str]");
    str.print("[str_copy]");

    SimpleString str_move{ std::move(str_copy) };
    str_move.append_line("reference");
    str.print("[std]");
    str_move.print("[std_move]");
    // Will throw a std::runtime_error
    str_move.append_line("Random stuff");
}
