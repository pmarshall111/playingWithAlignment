#include <chrono>
#include <functional>
#include <iostream>
#include <memory>

// The compiler will automatically align this to 8 bytes.
struct MyStruct {
    long long a;
    char b[1];
};
const int SIZE_OF_MYSTRUCT_NO_ALIGN = 9;

template<typename Fn>
void runFuncPrintTime(Fn fn, const std::string& prefix) {
    auto start = std::chrono::high_resolution_clock::now();
    fn();
    auto end = std::chrono::high_resolution_clock::now();
    int ms = std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();
    std::cout << prefix << " execution time: " << ms << std::endl;
}

enum class WriteType {
    LINEAR,
    RANDOM
};

void writeAligned(std::unique_ptr<volatile MyStruct[]>& compilerArr, int size, WriteType writeType) {
    for (int i = 0; i<size; i++) {
        int idx = i;
        if (writeType == WriteType::RANDOM) {
            idx = rand() % size;
        }
        compilerArr[i].a = rand()-1;
        compilerArr[i].b[0] = char(rand()%(126-33) + 33); // Printable chars
    }
}

void writeNonAligned(std::unique_ptr<volatile char[]>& nonAligned, int size, WriteType writeType) {
    for (int i = 0; i<size; i++) {
        int idx = i;
        if (writeType == WriteType::RANDOM) {
            idx = rand() % size;
        }
        *reinterpret_cast<volatile long long*>(&nonAligned[i*SIZE_OF_MYSTRUCT_NO_ALIGN]) = rand()-1;
        nonAligned[i*SIZE_OF_MYSTRUCT_NO_ALIGN+4] = char(rand()%(126-33) + 33); // Printable chars
    }
}

int main() {
    int numStructs = 100000000;

    // Letting the compiler do it's thing
    std::unique_ptr<volatile MyStruct[]> compilerArray = std::make_unique<volatile MyStruct[]>(numStructs);
    // Rolling my own
    std::unique_ptr<volatile char[]> nonAligned = std::make_unique<volatile char[]>(SIZE_OF_MYSTRUCT_NO_ALIGN * numStructs);

    std::cout << "Total memory allocated by compiler (mb): " << numStructs * sizeof(MyStruct) / 1000000 << std::endl;
    std::cout << "Total memory allocated by me (mb): " << numStructs * SIZE_OF_MYSTRUCT_NO_ALIGN / 1000000 << std::endl;

    // Run a few times for multiple results
    runFuncPrintTime([&](){writeNonAligned(nonAligned, numStructs, WriteType::LINEAR);}, "Write non aligned arr linear access");
    runFuncPrintTime([&](){writeAligned(compilerArray, numStructs, WriteType::LINEAR);}, "Write compiler arr linear access");
    runFuncPrintTime([&](){writeNonAligned(nonAligned, numStructs, WriteType::RANDOM);}, "Write non aligned arr random access");
    runFuncPrintTime([&](){writeAligned(compilerArray, numStructs, WriteType::RANDOM);}, "Write compiler arr random access");
    runFuncPrintTime([&](){writeNonAligned(nonAligned, numStructs, WriteType::LINEAR);}, "Write non aligned arr linear access");
    runFuncPrintTime([&](){writeAligned(compilerArray, numStructs, WriteType::LINEAR);}, "Write compiler arr linear access");
    runFuncPrintTime([&](){writeNonAligned(nonAligned, numStructs, WriteType::RANDOM);}, "Write non aligned arr random access");
    runFuncPrintTime([&](){writeAligned(compilerArray, numStructs, WriteType::RANDOM);}, "Write compiler arr random access");
    runFuncPrintTime([&](){writeNonAligned(nonAligned, numStructs, WriteType::LINEAR);}, "Write non aligned arr linear access");
    runFuncPrintTime([&](){writeAligned(compilerArray, numStructs, WriteType::LINEAR);}, "Write compiler arr linear access");
    runFuncPrintTime([&](){writeNonAligned(nonAligned, numStructs, WriteType::RANDOM);}, "Write non aligned arr random access");
    runFuncPrintTime([&](){writeAligned(compilerArray, numStructs, WriteType::RANDOM);}, "Write compiler arr random access");
    runFuncPrintTime([&](){writeNonAligned(nonAligned, numStructs, WriteType::LINEAR);}, "Write non aligned arr linear access");
    runFuncPrintTime([&](){writeAligned(compilerArray, numStructs, WriteType::LINEAR);}, "Write compiler arr linear access");
    runFuncPrintTime([&](){writeNonAligned(nonAligned, numStructs, WriteType::RANDOM);}, "Write non aligned arr random access");
    runFuncPrintTime([&](){writeAligned(compilerArray, numStructs, WriteType::RANDOM);}, "Write compiler arr random access");
    runFuncPrintTime([&](){writeNonAligned(nonAligned, numStructs, WriteType::LINEAR);}, "Write non aligned arr linear access");
    runFuncPrintTime([&](){writeAligned(compilerArray, numStructs, WriteType::LINEAR);}, "Write compiler arr linear access");
    runFuncPrintTime([&](){writeNonAligned(nonAligned, numStructs, WriteType::RANDOM);}, "Write non aligned arr random access");
    runFuncPrintTime([&](){writeAligned(compilerArray, numStructs, WriteType::RANDOM);}, "Write compiler arr random access");
}