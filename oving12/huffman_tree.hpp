//
// Created by odderikf on 11/8/18.
//

#ifndef OVING12_HUFFMAN_TREE_HPP
#define OVING12_HUFFMAN_TREE_HPP

#include <vector>
#include <zconf.h>
#include <boost/shared_ptr.hpp>
#include <fstream>

class huffman_tree {
public:
    class tree{
    public:
        tree *parent = nullptr;
        tree *left = nullptr;
        tree *right = nullptr;
        uint64_t value;
        char *character = nullptr;
        explicit tree(uint64_t value) : value(value){};
        ~tree(){
            delete left;
            delete right;
            delete character;
        }
    };

    std::vector<bool> findpath(const unsigned char &);
    std::vector<tree*> characters;
    tree* root;
    std::vector<std::vector<bool>> paths;

    explicit huffman_tree(std::vector<uint64_t> counts);
    ~huffman_tree(){
        delete root;
    }

    enum direction{
        LEFT = 0,
        RIGHT = 1
    };
};

void huffman_encode(const huffman_tree &, std::ifstream &, std::ofstream &);
void huffman_decode(const huffman_tree &, std::ifstream &, std::ofstream &);

#endif //OVING12_HUFFMAN_TREE_HPP
