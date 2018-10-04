//
// Created by odderikf on 9/6/18.
//

#include <iostream>
#include "NumberDoubleLinkedListPointer.hpp"
int MAXDIGIT = 9;
int nodecount = 0;

NumberDoubleLinkedList::NumberDoubleLinkedList(const std::string & s) {
    for (char c : s){
        emplace_back(c);
    }
}

NumberDoubleLinkedList NumberDoubleLinkedList::operator-() const{
    NumberDoubleLinkedList ret = NumberDoubleLinkedList();
    ret.negative = ~negative;
    auto i = top;
    while (i){
        ret.emplace_back(i->val);
        i = i->smaller;
    }
    return ret;
}

std::ostream &operator<<(std::ostream & o, const NumberDoubleLinkedList & l) {
    if (l.negative) o << '-';
    auto i = l.top;
    while (i){
        o << std::to_string(i->val);
        i = i->smaller;
    }
    return o;
}

void NumberDoubleLinkedList::emplace_back(const char & c) {
    if (top) {
        bottom->smaller = new Node(c);
        bottom->smaller->bigger = bottom;
        bottom = bottom->smaller;

    } else {
        bottom = top = new Node(c);
    }
    _size++;
}
void NumberDoubleLinkedList::emplace_back(const int & i) {
    if (top) {
        bottom->smaller = new Node(i);
        bottom->smaller->bigger = bottom;
        bottom = bottom->smaller;

    } else {
        bottom = top = new Node(i);
    }
    _size++;
}
void NumberDoubleLinkedList::emplace_front(const char & c) {
    if (top) {
        auto newtop = new Node(c);
        newtop->smaller = top;
        top = newtop;

    } else {
        bottom = top = new Node(c);
    }
    _size++;
}
void NumberDoubleLinkedList::emplace_front(const int & i) {
    if (top) {
        auto newtop = new Node(i);
        newtop->smaller = top;
        top = newtop;

    } else {
        bottom = top = new Node(i);
    }
    _size++;
}

NumberDoubleLinkedList NumberDoubleLinkedList::operator+(const NumberDoubleLinkedList & that) const{
    auto i = this->bottom, j = that.bottom;
    auto ret = NumberDoubleLinkedList();

    bool rest = false;
    while (i or j){
        int v = rest;
        if(i) v+=i->val;
        if(j) v+=j->val;
        rest = false;
        if (v > MAXDIGIT){
            rest = true;
            v -= MAXDIGIT + 1;
        }
        ret.emplace_front(v);
        if(i) i = i->bigger;
        if(j) j = j->bigger;
    }
    if(rest){
        ret.emplace_front(1);
    }
    return ret;
}

NumberDoubleLinkedList NumberDoubleLinkedList::operator-(const NumberDoubleLinkedList & that) const {
    if (*this < that) return -(that - *this);
    auto i = this->bottom, j = that.bottom;
    auto ret = NumberDoubleLinkedList();

    bool rest = false;
    while (i){
        int v = -rest;
        v += i->val;
        if(j) v -= j->val;
        rest = false;
        if (v < 0){
            rest = true;
            v += MAXDIGIT + 1;
        }
        ret.emplace_front(v);
        i = i->bigger;
        if(j) j = j->bigger;
    }
    if(rest){
        ret.negative = true;
    }
    while (ret.top->val == 0 and ret.top->smaller){
        ret.remove_front();
    }
    return ret;
}

NumberDoubleLinkedList::~NumberDoubleLinkedList() {
    for(auto i = top; i != bottom; ){
        auto j = i->smaller;
        i->~Node();
        delete i;
        i = nullptr;
        i = j;
    }
    bottom = nullptr;
}
NumberDoubleLinkedList::Node::~Node(){
    this->smaller = nullptr;
    this->bigger = nullptr;

}
bool NumberDoubleLinkedList::operator>(const NumberDoubleLinkedList & that) const {
    if(that.size() > this->size()) return false;
    if(that.size() < this->size()) return true;

    auto i = top, j = that.top;
    while (i){
        if (i->val < j->val) return false;
        if (i->val > j->val) return true;
        i = i->smaller;
        j = j->smaller;
    }
    return false;
}

bool NumberDoubleLinkedList::operator<(const NumberDoubleLinkedList& that) const{
    return that > *this;
}

bool NumberDoubleLinkedList::operator==(const NumberDoubleLinkedList & that) const {
    if (size() != that.size()) return false;
    auto i = top, j = that.top;
    while (i){
        if (i->val != j->val) return false;
        i = i->smaller;
        j = j->smaller;
    }
    return true;
}

int NumberDoubleLinkedList::size() const{
    return _size;
}

void NumberDoubleLinkedList::remove_front() {
    top = top->smaller;
    _size--;
}

NumberDoubleLinkedList::Node::Node(const char & c) {
    val = c - '0';
    nodecount++;
}

NumberDoubleLinkedList::Node::Node(const int & i) : val(i){ nodecount++; }

/**
NumberDoubleLinkedList::Node &NumberDoubleLinkedList::Node::operator=(const NumberDoubleLinkedList::Node & that) {
    this->val = that.val;
    this->bigger = that.bigger;
    this->smaller = that.smaller;
    return *this;
}

**/