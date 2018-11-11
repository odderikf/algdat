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

    while (queue.size != 1){

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

void huffman_encode(const huffman_tree &huffman, std::ifstream &file_in, std::ofstream &file_out){
    char buffer_read[BLOCK_SIZE];
    char buffer_write[BLOCK_SIZE];
    int write_index = 0;

    char buffer_bool = 0;
    char bool_index = 0;

    file_in.clear();
    file_in.seekg(0);

    file_out.clear();
    file_out.seekp(COUNTS_SIZE+1);

    do{
        file_in.read(buffer_read, BLOCK_SIZE);
        std::cout << "read " << file_in.gcount() << " bytes" << std::endl;
        for(int i = 0; i < file_in.gcount(); i++){
            auto c  = static_cast<unsigned char>(buffer_read[i]);
            auto decisions = huffman.paths[c];
            for (bool d : decisions){
                //std::cout << d << std::endl;
                buffer_bool |= d << bool_index++;

                if (bool_index == 8){
                    buffer_write[write_index++] = buffer_bool;
                    buffer_bool = bool_index = 0;

                    if (write_index == BLOCK_SIZE){
                        file_out.write(buffer_write, BLOCK_SIZE);
                        std::cout << "wrote " << BLOCK_SIZE << " bytes" << std::endl;
                        write_index = 0;
                    }
                }
            }
        }
    } while (file_in.gcount() > 0);

    buffer_write[write_index++] = buffer_bool;
    file_out.write(buffer_write, write_index);

    buffer_write[0] = bool_index; // lets me know how many bits to skip at end

    file_out.clear();
    file_out.seekp(COUNTS_SIZE);
    file_out.write(buffer_write, 1);

    std::cout << "wrote " << write_index << " bytes" << std::endl;
}

void huffman_decode(const huffman_tree &huffman, std::ifstream &file_in, std::ofstream &file_out){
    char buffer_read[BLOCK_SIZE];
    char buffer_write[BLOCK_SIZE];
    int write_index = 0;

    char buffer_bool = 0;

    huffman_tree::tree *position = huffman.root;

    file_in.seekg(COUNTS_SIZE);
    file_in.clear();
    file_in.read(buffer_read, 1);

    char bits_to_skip = buffer_read[0];
    signed int max_bit_index = 8;

    do {
        file_in.read(buffer_read, BLOCK_SIZE);
        std::cout << "read " << file_in.gcount() << " bytes" << std::endl;
        for(short i = 0; i <= file_in.gcount(); ++i){
            buffer_bool = buffer_read[i];
            if (file_in.eof() and i == file_in.gcount()){
                max_bit_index -= static_cast<unsigned char>(bits_to_skip);
            }
            for(signed int j = 0; j < max_bit_index; ++j){
                bool direction = static_cast<bool>((buffer_bool >> j) & 1);
                //std::cout << direction << std::endl;
                if ( direction == huffman_tree::LEFT){
                    position = position->left;
                } else if (direction == huffman_tree::RIGHT){
                    position = position->right;
                }

                if (position->character != nullptr){
                    buffer_write[write_index++] = *(position->character);
                    position = huffman.root;

                    if (write_index == BLOCK_SIZE) {
                        file_out.write(buffer_write, BLOCK_SIZE);
                        std::cout << "wrote " << BLOCK_SIZE << " bytes" << std::endl;
                        write_index = 0;
                    }
                }

            }
        }
    } while (not file_in.eof());

    file_out.write(buffer_write, write_index);
    std::cout << "wrote " << write_index << " bytes" << std::endl;
}