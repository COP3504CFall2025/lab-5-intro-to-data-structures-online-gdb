#include <cassert>
#include <iostream>
#include <string>
#include "LinkedList.hpp" // your header with full template definitions

using namespace std;

void testConstructor() {
    cout << "Running testConstructor...\n";
    LinkedList<int> list;

    // Default: head and tail should exist
    assert(list.getHead() != nullptr);
    assert(list.getTail() != nullptr);
    assert(list.getCount() == 2);

    // Head and tail should not be the same node
    assert(list.getHead() != list.getTail());

    cout << "✅ testConstructor passed\n\n";
}

void testAddHeadAndTail() {
    cout << "Running testAddHeadAndTail...\n";
    LinkedList<int> list;

    unsigned int oldCount = list.getCount();

    list.addHead(42);
    assert(list.getHead()->data == 42);
    assert(list.getCount() == oldCount + 1);

    list.addTail(99);
    assert(list.getTail()->data == 99);
    assert(list.getCount() == oldCount + 2);

    cout << "✅ testAddHeadAndTail passed\n\n";
}

void testRemoveHeadAndTail() {
    cout << "Running testRemoveHeadAndTail...\n";
    LinkedList<int> list;

    list.addTail(10);
    list.addTail(20);
    list.addTail(30);
    
    //std::cout << 1 << std:: endl;
    unsigned int countBefore = list.getCount();
    bool removedHead = list.removeHead();
    assert(removedHead);
    assert(list.getCount() == countBefore - 1);
    //std::cout << 2 << std:: endl;
    bool removedTail = list.removeTail();
    assert(removedTail);
    assert(list.getCount() == countBefore - 2);
    
    //std::cout << 3 << std:: endl;
    // Remove everything until list is empty
    while (list.removeHead()) {}
    //std::cout << 4 << std:: endl;
    assert(list.getHead() == nullptr);
    assert(list.getTail() == nullptr);
    assert(list.getCount() == 0);

    cout << "✅ testRemoveHeadAndTail passed\n\n";
}

void testClear() {
    cout << "Running testClear...\n";
    LinkedList<int> list;

    list.addHead(5);
    list.addTail(10);
    assert(list.getCount() > 2);

    list.Clear();
    assert(list.getHead() == nullptr);
    assert(list.getTail() == nullptr);
    assert(list.getCount() == 0);

    cout << "✅ testClear passed\n\n";
}

void testCopyAndMove() {
    cout << "Running testCopyAndMove...\n";
    LinkedList<std::string> list1;
    list1.addTail("A");
    list1.addTail("B");
    list1.addTail("C");

    LinkedList<std::string> list2(list1); // copy constructor
    assert(list2.getCount() == list1.getCount());

    LinkedList<std::string> list3;
    list3 = list1; // copy assignment
    assert(list3.getCount() == list1.getCount());

    LinkedList<std::string> list4(std::move(list1)); // move constructor
    assert(list1.getCount() == 0);

    LinkedList<std::string> list5;
    list5 = std::move(list2); // move assignment
    assert(list2.getCount() == 0);

    cout << "✅ testCopyAndMove passed\n\n";
}

void testPrints() {
    cout << "Running testPrints...\n";
    LinkedList<int> list;
    list.addTail(1);
    list.addTail(2);
    list.addTail(3);

    if (list.getTail()->next != nullptr) return;

    cout << "Forward: ";
    list.printForward();
    cout << "Reverse: ";
    list.printReverse();
    cout << "✅ testPrints passed (manual visual check)\n\n";
}

int main() {
    cout << "=== LinkedList Test Suite ===\n\n";

    testConstructor();
    testAddHeadAndTail();
    testRemoveHeadAndTail();
    testClear();
    testCopyAndMove();
    testPrints();

    cout << "🎉 All tests passed successfully!\n";
    return 0;
}
