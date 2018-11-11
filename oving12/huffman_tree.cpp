//
// Created by odderikf on 11/8/18.
//

#include <limits>
#include <algorithm>
#include <iostream>
#include "huffman_tree.hpp"
#include "../mylib/heap.hpp"
#include "constants.hpp"

huffman_tree::huffman_tree(std::vector<uint64_t> counts){

    std::vector<tree*> temp;
    temp.reserve(BYTE_SIZE*2-1);
    characters.reserve(counts.size());

    for(uint64_t i = 0; i < counts.size(); i++){
        auto *t = new tree(counts[i]);
        t->character = new char(static_cast<char>(i));
        characters.insert(characters.begin()+i, t);
        temp.emplace_back(t);
    }

    std::function<bool(tree*, tree*)> lessthan;
    lessthan = [&lessthan](tree* t1, tree* t2){
        if (t1 == t2) return false;
        if( t1->value == t2->value ) {
            if (t1->character != nullptr and t2->character != nullptr) {
                return *(t1->character) < *(t2->character);
            } else if (t1->character == t2->character) { // both are nullptr
                return lessthan(t1->right, t2->right);
            } else {
                return t1->character != nullptr; // characters are more valuable than noncharacters
            }
        }
        return t1->value < t2->value;
    };

    my::Heap<tree*> queue(temp, my::Heap<tree*>::MIN_HEAP, lessthan);

    while (queue.size > 1){

        tree *min1 = queue.pop_min();
        tree *min2 = queue.pop_min();

        tree *parent = new tree(min1->value + min2->value);
        parent->left = min1;
        min1->parent = parent;

        parent->right = min2;
        min2->parent = parent;

        queue.emplace(parent);
    }

    root = queue.pop();

    paths.reserve(BYTE_SIZE);
    for(unsigned short i = 0; i < BYTE_SIZE; ++i){
        paths.emplace_back(findpath(static_cast<const unsigned char &>(i)));
    }
}

std::vector<bool> huffman_tree::findpath(const unsigned char &c){
    std::vector<bool> decisions;
    tree *current;
    current = characters[c];

    while (current != root){

        tree *parent = current->parent;
        if (parent->left == current) decisions.emplace_back(huffman_tree::LEFT);
        else decisions.emplace_back(huffman_tree::RIGHT);
        current = parent;
    }
    std::reverse(decisions.begin(), decisions.end());
    return decisions;
}
