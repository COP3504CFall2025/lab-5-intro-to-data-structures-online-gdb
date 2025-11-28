#pragma once

#include <cstddef>
#include <vector>
#include <stdexcept>


template <typename T>
class StackInterface {

    std::vector<T> myData;

public:

    void push(const T& item) {
        myData.push_back(item);
    }
    T pop() {
        if (myData.empty()) {
            throw std::out_of_range("Stack is empty");
        }
        T theT = peek();
        myData.pop_back();

        return theT;

    }

    T peek() const {
         if (myData.empty()) {
            throw std::out_of_range("Stack is empty");
        }
        return myData[myData.size()-1];
    }

    std::size_t getSize() const noexcept {
        return myData.size();
    }

};



template <typename T>
class QueueInterface {
    std::vector<T> data;
public:
    void enqueue(const T& item) {
        data.push_back(item);
    }
    T dequeue() {
        if (data.empty()) {
            throw std::out_of_range("Empty brochacho");
        }
        T theT = data[0];

        data.erase(data.begin());

        return theT;
    }

    T peek() const {
        if (data.empty()) {
            throw std::out_of_range("Empty brochacho");
        }

        return data[0];
    }
    std::size_t getSize() const noexcept {
        return data.size();
    }
};



template <typename T>
class DequeInterface {
    std::vector<T> data;
public:
    void pushFront(const T& item) {
        data.insert(data.begin(), item);
    }
    void pushBack(const T& item) {
        data.push_back(item);
    }
    T popFront() {
        if (data.empty()) throw std::out_of_range("Empty");

        T theT = data[0];
        data.erase(data.begin());
        return theT;
    }

    T popBack() {
        if (data.empty()) throw std::out_of_range("Empty");
        T theT = data[data.size()-1];
        data.pop_back();
        return theT;
    }
    const T& front() const {
        if (data.empty()) throw std::out_of_range("Empty");
        return data[0];
    }
    const T& back() const {
        if (data.empty()) throw std::out_of_range("Empty");
        return data[data.size()-1];
    }
    std::size_t getSize() const noexcept {
        return data.size();
    }
};

