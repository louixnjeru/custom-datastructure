#pragma once

#include "data_structure.h"
#include "data_container.h"

#include <thread>
#include <vector>
#include <mutex>
#include <iostream>
#include <strstream>
#include <any>

VectorContainer::VectorContainer(size_t size) : size(size) {
    arr.reserve(size);
}

void VectorContainer::push_back(I_DataItem &new_data) {
    std::lock_guard<std::mutex> lock(vectorMutex);
    arr.push_back(std::make_unique<I_DataItem>(new_data));
}

const I_DataItem& VectorContainer::operator[](size_t num) {
    return *arr.at(num);
}