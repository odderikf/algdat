//
// Created by odderikf on 9/6/18.
//

#ifndef OVING4_NUMBERDOUBLELINKEDLIST_HPP
#define OVING4_NUMBERDOUBLELINKEDLIST_HPP


#include <string>
#include <bits/unique_ptr.h>
#include <memory>

class NumberDoubleLinkedList {
public:
    explicit NumberDoubleLinkedList(const std::string&);
    NumberDoubleLinkedList() = default;
    NumberDoubleLinkedList operator+(const NumberDoubleLinkedList&) const;
    NumberDoubleLinkedList operator-(const NumberDoubleLinkedList&) const;
    NumberDoubleLinkedList operator-() const;
    bool operator>(const NumberDoubleLinkedList&) const;
    bool operator<(const NumberDoubleLinkedList&) const;
    bool operator==(const NumberDoubleLinkedList&) const;
    NumberDoubleLinkedList& operator=(const NumberDoubleLinkedList&) = default;
    friend std::ostream& operator<<(std::ostream&, const NumberDoubleLinkedList&);
    void remove_front();
    int size() const;
    ~NumberDoubleLinkedList();
    bool negative = false;
private:
    void emplace_back(const char&);
    void emplace_back(const int&);
    void emplace_front(const char&);
    void emplace_front(const int&);
    class Node;
    Node *bottom;
    Node *top = nullptr;
    int _size = 0;
};

class NumberDoubleLinkedList::Node {
public:
    Node(const char&);
    Node(const int &);
    Node& operator=(Node const&) = default;
    ~Node();

    Node *smaller = nullptr;
    Node *bigger;
    int8_t val = -1;
};




#endif //OVING4_NUMBERDOUBLELINKEDLIST_HPP
