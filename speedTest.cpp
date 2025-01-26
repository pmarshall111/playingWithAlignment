#include <chrono>
#include <functional>
#include <iostream>
#include <memory>

// The compiler will automatically align this to 4 bytes.
struct MyStruct {
    int a;
    char b[1];
    int c;
};

template<typename Fn>
void runFuncPrintTime(Fn fn, const std::string& prefix) {
    auto start = std::chrono::high_resolution_clock::now();
    fn();
    auto end = std::chrono::high_resolution_clock::now();
    int ms = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    std::cout << prefix << " execution time: " << ms << std::endl;
}

void populateCompilerArr(std::unique_ptr<MyStruct[]>& compilerArr, int size) {
    for (int i = 0; i<size; i++) {
        compilerArr[i].a = i+1;
        compilerArr[i].b[0] = char(i%(126-33) + 33); // Printable chars
        compilerArr[i].c = i+2;
    }
}

void populateMyArr(std::unique_ptr<char[]>& myArr, int size) {
    for (int i = 0; i<size; i++) {
        myArr[i*9] = i+1;
        myArr[i*9+4] = char(i%(126-33) + 33); // Printable chars
        myArr[i*9+5] = i+2;
    }
}

void updateCompilerArr(std::unique_ptr<MyStruct[]>& compilerArr, int size) {
    for (int i = 0; i<size; i++) {
        compilerArr[i].c = i-1;
    }
}

void updateMyArr(std::unique_ptr<char[]>& myArr, int size) {
    for (int i = 0; i<size; i++) {
        myArr[i*9+5] = i-1;
    }
}

int main() {
    int numStructs = 10000000;

    // Letting the compiler do it's thing
    std::unique_ptr<MyStruct[]> compilerArray = std::make_unique<MyStruct[]>(numStructs);
    // Rolling my own
    std::unique_ptr<char[]> myArray = std::make_unique<char[]>(9 * numStructs);

    std::cout << "Total memory allocated by compiler (mb): " << numStructs * sizeof(MyStruct) / 1000000 << std::endl;
    std::cout << "Total memory allocated by me (mb): " << numStructs * 9 / 1000000 << std::endl;

    // Fill structs with the same data
    runFuncPrintTime([&](){populateCompilerArr(compilerArray, numStructs);}, "Populate compiler arr");
    runFuncPrintTime([&](){populateMyArr(myArray, numStructs);}, "Populate my arr");

    // Loop through structs and change the non-aligned member 'c'
    runFuncPrintTime([&](){updateCompilerArr(compilerArray, numStructs);}, "Update compiler arr");
    runFuncPrintTime([&](){updateMyArr(myArray, numStructs);}, "Update my arr");
}