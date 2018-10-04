//
// Created by odderikf on 9/6/18.
//

#include <iostream>
#include <stdexcept>
#include "NumberDoubleLinkedList.hpp"
const int MAXDIGIT = 9;

NumberDoubleLinkedList::NumberDoubleLinkedList(const std::string & s) {
    if(s.front() == '-'){
	negative = true;
	for(auto i = s.begin()+1; i<s.end(); i++){
	    emplace_back(*i);
	}
    }else{
        for (char c : s){
            emplace_back(c);
        }
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
        bottom.lock()->smaller = std::make_shared<Node>(Node(c));
        bottom.lock()->smaller->bigger = bottom;
        bottom = bottom.lock()->smaller;
    } else {
        bottom = top = std::make_shared<Node>(Node(c));
    }
    _size++;
}
void NumberDoubleLinkedList::emplace_back(const int & i) {
    if (top) {
        bottom.lock()->smaller = std::make_shared<Node>(Node(i));
        bottom.lock()->smaller->bigger = bottom;
        bottom = bottom.lock()->smaller;

    } else {
        bottom = top = std::make_shared<Node>(Node(i));
    }
    _size++;
}
void NumberDoubleLinkedList::emplace_front(const char & c) {
    if (top) {
        auto newtop = std::make_shared<Node>(Node(c));
        newtop->smaller = top;
        top = newtop;

    } else {
        bottom = top = std::make_shared<Node>(Node(c));
    }
    _size++;
}
void NumberDoubleLinkedList::emplace_front(const int & i) {
    if (top) {
        auto newtop = std::make_shared<Node>(Node(i));
        newtop->smaller = top;
        top->bigger = newtop;
        top = newtop;

    } else {
        bottom = top = std::make_shared<Node>(Node(i));
    }
    _size++;
}

NumberDoubleLinkedList NumberDoubleLinkedList::operator+(const NumberDoubleLinkedList & that) const{
    auto i = this->bottom.lock(), j = that.bottom.lock();
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
        if(i) i = i->bigger.lock();
        if(j) j = j->bigger.lock();
    }
    if(rest){
        ret.emplace_front(1);
    }
    return ret;
}

NumberDoubleLinkedList NumberDoubleLinkedList::operator-(const NumberDoubleLinkedList & that) const {
    if (*this < that) return -(that - *this);
    auto i = this->bottom.lock(), j = that.bottom.lock();
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
        i = i->bigger.lock();
        if(j) j = j->bigger.lock();
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
    if (not std::isdigit(c)) throw std::invalid_argument(std::string("Invalid character ")+c+": Not a digit");
    val = c - '0';
}

NumberDoubleLinkedList::Node::Node(const int & i) : val(i){ }

/**
NumberDoubleLinkedList::Node &NumberDoubleLinkedList::Node::operator=(const NumberDoubleLinkedList::Node & that) {
    this->val = that.val;
    this->bigger = that.bigger;
    this->smaller = that.smaller;
    return *this;
}

**/
