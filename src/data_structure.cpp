#include "data_structure.h"

#include <thread>
#include <vector>
#include <mutex>
#include <any>

std::ostream& operator<< (std::ostream &os, const I_DataItem &item) {
    item.print(os);
    return os;
}
