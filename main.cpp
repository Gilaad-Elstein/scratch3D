#include <iostream>
#include <chrono>
#include "Engine.h"

int main() {
    auto start = std::chrono::high_resolution_clock::now();

    Engine::run();
//    Engine::TextureMapViewer();

    auto finish = std::chrono::high_resolution_clock::now();
    std::chrono::duration<float> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";

    return 0;
}
