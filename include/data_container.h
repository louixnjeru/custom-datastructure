#pragma once

#include "data_structure.h"

#include <thread>
#include <vector>
#include <mutex>
#include <iostream>
#include <strstream>
#include <any>

class VectorContainer {
    private:
        size_t size;
        std::vector<std::unique_ptr<I_DataItem>> arr;
        std::mutex vectorMutex;

    public:
        VectorContainer(size_t size);

        void push_back(I_DataItem &new_data);

        const I_DataItem& operator[](size_t num);

        

};
