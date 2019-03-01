#include <iostream>
#include "String.h"

int main() {
    String s ("hello");
    String s1('b', 5);
    s.print();
    s1.print();
    String s2 = s1;
    s2.append(4);
    s2.append(s1);
    std::cout << s2.toString() << std::endl;
    std::cout << s.toString() << std::endl;
    std::cout << s1.toString() << std::endl;
    String s4("lil");
    std::cout << s4.toString() << std::endl;
    s4.print();
    s4 = s2;
    std::cout << s4.toString() << std::endl;
    s4.print();
    s.append(s);
    std::cout << s.toString() << std::endl;
    s.append('c');
    s.append(" cartoon\n");
    s.append(s1);
    std::cout << s.toString() << std::endl;
    s.print();
    std::cout << s2.toString() << std::endl;
    std::cout << s.toString() << std::endl;
    String hello("hello");
    hello.append(", ");
    hello.append(hello);
    hello.append("World!");
    std::cout << hello.toString() << std::endl;
    hello.reverse();
    std::cout << hello.toString() << std::endl;
    std::cout << hello.charAt(4) << std::endl;
    std::cout << hello.suffix(2).toString() << std::endl;
    std::cout << hello.postfix(2).toString() << std::endl;
    std::cout << hello.substring(2, 3).toString() << std::endl;
    hello += hello;
    hello.reverse();
    std::cout << hello.toString() << std::endl;
    String s5('8', 9);
    std::cout << "'" << hello.toString() << "'" << " is Digit? " << (hello.isDigit() ? "Yes" : "No") << std::endl;
    std::cout << "'" << s5.toString() << "'" << " is Digit? " << (s5.isDigit() ? "Yes" : "No") << std::endl;
    std::cout << "'" << hello.substring(0, 4).toString() << "'" << " is Alpha? " << (hello.substring(0, 4).isAlpha() ? "Yes" : "No") << std::endl;
    std::cout << "'" << s5.toString() << "'" << " is Alpha? " << (s5.isAlpha() ? "Yes" : "No") << std::endl;
    std::cout << hello.find('W') << std::endl;
    std::cout << hello.rfind('W') << std::endl;
    return 0;
}
