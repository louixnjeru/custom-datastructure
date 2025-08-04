#pragma once

#include <thread>
#include <vector>
#include <mutex>
#include <iostream>
#include <strstream>
#include <any>


// Interface base class - Allows pointers to template class
class I_DataItem {
    public:
        virtual std::any getData() = 0;
        virtual void setData(std::any newData) = 0;
        virtual ~I_DataItem() {};

        virtual void print(std::ostream &os) const = 0;

};

template <class T>
class DataItem : public I_DataItem {
    private:
        // Stores the actual data
        T data;
        // Mutex preventing races when writing
        std::mutex data_lock;
    public:
        DataItem(T new_data): data(new_data) {};
        virtual std::any getData() override {
            try {
                return std::any_cast<T>(data);
            } catch (std::bad_cast &e) {
                throw;
            }
        }

        // Sets the data in the class - std::any allows runtime polymorphism
        virtual void setData(std::any newData) override {
            // Acquires the lock
            std::lock_guard<std::mutex> lock(data_lock);
            try {
                // Tries to cast the data to type T
                data = std::any_cast<T>(newData);
                std::cout << "Value set to " << data << " by thread pid=" << std::this_thread::get_id() << std::endl;
            } catch (const std::bad_cast &e) {
                // Catches bad casts to prevent crash
                std::cout << "thread pid=" << std::this_thread::get_id() << " encountered bad cast: " << e.what() << std::endl;
            }
        }

        // Allows the data - If data is class then overload << operator in class
        virtual void print(std::ostream &os) const override {
            os << data;
        }

        bool operator== (I_DataItem* other) {
            return this->data == other->d
        }
};

std::ostream& operator<< (std::ostream &os, const I_DataItem &item);