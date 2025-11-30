#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include <utility>
#include <cmath>

template <typename T>
class ABDQ : public DequeInterface<T> {
public:
    T* data_;                 // underlying dynamic array
    std::size_t capacity_;    // total allocated capacity
    std::size_t size_;        // number of stored elements
    std::size_t front_;       // index of front element
    std::size_t back_;        // index after the last element (circular)

    static constexpr std::size_t SCALE_FACTOR = 2;

    //Covers negative cases (for example, -1 % 5)
    size_t mod(int a, size_t b) {
        if (a < 0) {
            a += std::ceil(std::abs(static_cast<double>(a)/b)) * b;
        }
    
        return a % b;
    }

    void size_up() {
        if (size_ >= capacity_) {
            size_t old_capacity = capacity_;
            size_t old_front = front_;
            if (front_ <= back_) front_ += capacity_ * (SCALE_FACTOR-1);
            capacity_ *= SCALE_FACTOR;

            T* new_data = new T[capacity_];
            for (size_t i=0;i< size_;i++) {
                new_data[index(i)] = data_[(old_front + i) % old_capacity];
            }
            delete[] data_;
            data_ = new_data;
        }
    }

    void size_down() {
        if (size_ < capacity_/SCALE_FACTOR) {
            size_t old_capacity = capacity_;
            capacity_ /= SCALE_FACTOR;

            T* new_data = new T[capacity_];
            for (size_t i=0;i< size_;i++) {
                new_data[index(i)] = data_[(front_ + i) % old_capacity];
            }
            delete[] data_;
            data_ = new_data;
        }
    }

    size_t index(size_t i) {return (front_ + i) % capacity_;}


public:
    // Big 5
    ABDQ() : ABDQ(4) {}

    explicit ABDQ(std::size_t capacity) : capacity_(capacity), size_(0), front_(0), back_(0) {
        data_ = new T[capacity_];
    }

    ABDQ(const ABDQ& other) : capacity_(other.capacity_), size_(other.size_), front_(other.front_), back_(other.back_) {
        data_ = new T[capacity_];

        for (size_t i = 0; i < size_; i++) {
            data_[index(i)] = other.data_[index(i)];
        }
    }

    ABDQ(ABDQ&& other) noexcept : data_(other.data_), capacity_(other.capacity_), size_(other.size_), front_(other.front_), back_(other.back_){
        other.data_ = nullptr;
        other.capacity_ = other.size_ = other.front_ = other.back_ = 0;
    }

    ABDQ& operator=(const ABDQ& other) {
        if (this == &other) return *this;

        T* new_data = new T[other.capacity_];
        for (size_t i = 0; i < other.size_; i++) {
            size_t index = (other.front_ + i) % other.capacity_;
            new_data[index] = other.data_[index];
        }
        delete[] data_;
        data_ = new_data;

        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;

        return *this;
    }
    ABDQ& operator=(ABDQ&& other) noexcept {
        if (this == &other) return *this;

        data_ = other.data_;
        capacity_ = other.capacity_;
        size_ = other.size_;
        front_ = other.front_;
        back_ = other.back_;

        other.data_ = nullptr;
        other.capacity_ = other.size_ = other.front_ = other.back_ = 0;

        return *this;
    }

    ~ABDQ() override {
        delete[] data_;
    }

    // Insertion
    void pushFront(const T& item) override {
        size_up();
        front_ = mod((front_-1), capacity_);
        
        data_[front_] = item;
        size_++;
    }

    void pushBack(const T& item) override {
        size_up();
        data_[back_] = item;

        back_ = (back_+1) % capacity_;

        size_++;
    }

    // Deletion
    T popFront() override {
        T result = front();

        size_down();
        front_ = (front_+1) % capacity_;
        size_--;
        return result;
    }
    T popBack() override {
        T result = back();
    
        size_down();
        back_ = mod((back_-1), capacity_);
        size_--;

        return result;
    }

    // Access
    const T& front() const override {
        if (size_ == 0) throw std::runtime_error("Empty");
        return data_[front_];
    }
    const T& back() const override {
        if (size_ == 0) throw std::runtime_error("Empty");
        return data_[(back_-1)%capacity_];
    }

    // Getters
    std::size_t getSize() const noexcept override {return size_;}

    void shrinkIfNeeded() {size_down();}

};
