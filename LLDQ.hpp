#pragma once

#include <cstddef>
#include <stdexcept>
#include "Interfaces.hpp"
#include "LinkedList.hpp"
#include <utility>



template <typename T>
class LLDQ : public DequeInterface<T> {
private:
    LinkedList<T> list;

public:
    // Constructor
    LLDQ() {}

    // Core Insertion Operations
    void pushFront(const T& item) override {
        list.addHead(item);
    }

    void pushBack(const T& item) override  {
        list.addTail(item);
    }

    // Core Removal Operations
    T popFront() override {
        T result = front();
        list.removeHead();
        return result;
    }

    T popBack() override {
        T result = back();
        list.removeTail();
        return result;
    }

    // Element Accessors
    const T& front() const override {
        if (getSize()==0) throw std::runtime_error("Empty");
        return list.getHead()->data;
    }

    const T& back() const override {
        if (getSize()==0) throw std::runtime_error("Empty");
        return list.getTail()->data;
    }

    // Getter
    std::size_t getSize() const noexcept override {return list.getCount();}
};






