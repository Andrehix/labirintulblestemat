#include <iostream>
#include "Example.h"

void Example::f() const {
    std::cout << "private function f: " << x << "\n";
}

void Example::g() {
    ++y;
    f();
    std::cout << "public function g: " << y << "\n";
}
