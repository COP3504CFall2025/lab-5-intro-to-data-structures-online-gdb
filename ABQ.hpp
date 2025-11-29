#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"

// Technically bad, but size_t isn't likely to conflict with any client code.
using std::size_t;

template<typename T>
class ABQ : public QueueInterface<T>{

    size_t capacity_;
    size_t curr_size_;
    T* array_;
    static constexpr size_t scale_factor_ = 2;

public:
    // Constructors + Big 5
    ABQ()  : ABq(1) {}
    
    explicit ABQ(const size_t capacity) : capacity_(capacity), curr_size_(0) {
        array_ = new T[capacity_];
    };

    ABQ(const ABQ& other) : capacity_(other.capacity_), curr_size_(other.curr_size_) {
        array_ = new T[capacity_];

        for (size_t i=0; i< curr_size_; i++) {
            array_[i] = other.array_[i];
        }
    }

    ABQ& operator=(const ABQ& rhs) {
        if (this == &rhs) return *this;

        T* new_array = new T[rhs.capacity_];
        for (size_t i=0; i< rhs.curr_size_; i++) {
            new_array[i] = rhs.array_[i];
        }

        delete[] array_;

        capacity_ = rhs.capacity_;
        curr_size_ = rhs.curr_size_;
        array_ = new_array;

        return *this;
    }


    ABQ(ABQ&& other) noexcept {
        other.array_ = nullptr;
        other.curr_size_ = 0;
        other.capacity_ = 0;
    }

    ABQ& operator=(ABQ&& rhs) noexcept {
        if (this == &rhs) return *this;

        delete[] array_;

        array_ = rhs.array_;
        curr_size_ = rhs.curr_size_;
        capacity_ = rhs.capacity_;

        rhs.array_ = nullptr;
        rhs.curr_size_ = 0;
        rhs.capacity_ = 0;

        return *this;
    }

    ~ABQ() noexcept override {
        delete[] array_;
        curr_size_ = 0;
        capacity_ = 0;
    }

    // Get the number of items in the ABS
    [[nodiscard]] size_t getSize() const noexcept override {return curr_size_;}

    // Get the max size of the ABS
    [[nodiscard]] size_t getMaxCapacity() const noexcept {return capacity_;}

    // Return underlying data for the stack
    [[nodiscard]] T* getData() const noexcept {return array_;}

    // Insertion
    void enqueue(const T& data) override  {
        if (curr_size_ == capacity_) {
            capacity_ *= scale_factor_;

            T* new_array = new T[capacity_];

            for (size_t i=0; i< curr_size_; i++) {
                new_array[i] = array_[i];
            }

            delete[] array_;

            array_ = new_array;
        }

        
        array_[curr_size_] = data;
        curr_size_++;
    }

    // Access
    T peek() const override{
        if (curr_size_ == 0) throw std::runtime_error("Empty!");
        
        return array_[0];
    }

    // Deletion
    T dequeue() override {
        T result = peek();

        T* new_array = new T[capacity_];

        for (int i=1; i< curr_size_;i++) {
            new_array[i-1] = array_[i];
        }

        delete[] array_;
        array_ = new_array;
        
        curr_size_--;

        if (curr_size_ < capacity_/scale_factor_) {
            capacity_ /= scale_factor_;
        }

        return result;
    }

};
