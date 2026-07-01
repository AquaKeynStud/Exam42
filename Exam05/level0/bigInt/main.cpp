#include <iostream>
#include "bigint.hpp"

int main(void)
{
    bigint a(42);
    bigint b(10);

    std::cout << "a = " << a << std::endl;
    std::cout << "b = " << b << std::endl;

    std::cout << "\n--- + ---" << std::endl;
    std::cout << "a + b = " << (a + b) << std::endl;

    std::cout << "\n--- ++ postfix ---" << std::endl;
    std::cout << "a++ = " << a++ << std::endl;
    std::cout << "a   = " << a << std::endl;

    std::cout << "\n--- ++ prefix ---" << std::endl;
    std::cout << "++a = " << ++a << std::endl;
    std::cout << "a   = " << a << std::endl;

    std::cout << "\n--- += ---" << std::endl;
    a += b;
    std::cout << "a += b -> " << a << std::endl;

    std::cout << "\n--- << digit shifting ---" << std::endl;
    std::cout << "b << 3 = " << (b << 3) << std::endl;

    std::cout << "\n--- <<= digit shifting ---" << std::endl;
    b <<= 2;
    std::cout << "b <<= 2 -> " << b << std::endl;

    std::cout << "\n--- >> digit shifting ---" << std::endl;
    std::cout << "b >> 1 = " << (b >> 1) << std::endl;

    std::cout << "\n--- >>= digit shifting ---" << std::endl;
    b >>= 1;
    std::cout << "b >>= 1 -> " << b << std::endl;

    std::cout << "\n--- comparaisons ---" << std::endl;

    bigint x(123);
    bigint y(123);
    bigint z(456);

    std::cout << "x = " << x << std::endl;
    std::cout << "y = " << y << std::endl;
    std::cout << "z = " << z << std::endl;

    std::cout << "x < z  : " << (x < z) << std::endl;
    std::cout << "x <= y : " << (x <= y) << std::endl;
    std::cout << "z > x  : " << (z > x) << std::endl;
    std::cout << "z >= y : " << (z >= y) << std::endl;
    std::cout << "x == y : " << (x == y) << std::endl;
    std::cout << "x != z : " << (x != z) << std::endl;

    std::cout << "\n--- gros nombres ---" << std::endl;

    bigint big(999999);
    std::cout << "big      = " << big << std::endl;
    std::cout << "big + 1  = " << (big + bigint(1)) << std::endl;
    std::cout << "big << 4 = " << (big << 4) << std::endl;
    std::cout << "big >> 2 = " << (big >> 2) << std::endl;

    return 0;
}