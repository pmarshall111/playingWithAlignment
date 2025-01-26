#include <iostream>

// The compiler will automatically align this to 4 bytes.
struct MyStruct {
    int a;
    char b[1];
    int c;
};

int main() {
    MyStruct s {5872, '_', 2};
    MyStruct * sPtr = &s;

    std::cout << "Size of MyStruct: " << sizeof(MyStruct) << std::endl;
    std::cout << "Size of members: A=" << sizeof(s.a) << " B=" << sizeof(s.b) << " C=" << sizeof(s.c) << std::endl;
    std::cout << "Total size of members: " << sizeof(s.a) + sizeof(s.b) + sizeof(s.c) << std::endl;
    std::cout << "Alignment bytes added: " << sizeof(MyStruct) - sizeof(s.a) - sizeof(s.b) - sizeof(s.c) << std::endl;

    std::cout << "-------------" << std::endl;

    // a will begin at address s+0bytes
    int a = *reinterpret_cast<int *>(sPtr);
    // b will begin at address s+4bytes
    std::string b = std::string(reinterpret_cast<char *>(sPtr)+4, 1);
    // c will begin at address s+8bytes despite b only taking 1 byte of space. Compiler has inserted some padding for efficiency.
    int c = *(reinterpret_cast<char *>(sPtr)+8);

    std::cout << "A: " << a << std::endl;
    std::cout << "B: " << b << std::endl;
    std::cout << "C: " << c << std::endl;

    // If we just look at the struct for the addresses and assume there's no alignment, we get garbage.
    int cWithoutThinkingAlignment = *(reinterpret_cast<char *>(sPtr)+5);
    std::cout << "C without thinking about alignment: " << cWithoutThinkingAlignment << std::endl;
}