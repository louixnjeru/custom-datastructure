#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <thread>

#include "main.h"


int main() {
    srand(0);
    std::vector<std::unique_ptr<I_DataItem>> vec;
    vec.emplace_back(std::make_unique<DataItem<int>>(43));
    vec.emplace_back(std::make_unique<DataItem<std::string>>("Hello"));
    vec.emplace_back(std::make_unique<DataItem<int>>(57));

    std::cout << "\nVec elements:\n";
    for (auto &ele : vec) {
        std::cout << *ele << std::endl;
    }
    std::cout << "\n";
    
    std::vector<std::thread> threads;

    for (int i{0}; i < 5; ++i) {
        int rand_num = rand() % vec.size();
        threads.emplace_back(&I_DataItem::setData, vec[rand_num].get(), std::any(50 + i * 10));
    }

    for(auto &t: threads) {
        t.join();
    }

    std::cout << "\nVec elements:\n";
    for (auto &ele : vec) {
        std::cout << *ele << std::endl;
    }
    std::cout << "\n";
    
    return 0;
}
