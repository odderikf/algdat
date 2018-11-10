#include <iostream>
#include <fstream>
#include <vector>

#include "huffman_tree.hpp"
#include "constants.hpp"


std::vector<uint64_t> count(std::ifstream &file_in, std::ofstream &file_out){

    char buffer_in[BLOCK_SIZE];
    auto *ubuffer_in = reinterpret_cast<unsigned char *>(buffer_in);

    std::vector<uint64_t> counts;
    counts.reserve(BYTE_SIZE);
    for (int i = 0; i < BYTE_SIZE; ++i) {
        counts.emplace_back(0);
    }

    do{
        file_in.read(buffer_in, BLOCK_SIZE);
        std::cout << "read " << file_in.gcount() << " bytes" << std::endl;
        for(int i = 0; i < file_in.gcount(); i++){
            unsigned char c = ubuffer_in[i];
            counts[c]++;
        }

    } while (file_in.gcount() > 0);

    char buffer_out[COUNTS_SIZE];
    int write_index = 0;

    for(uint64_t i : counts){
        buffer_out[write_index++] = static_cast<char>((i & 0xFF00000000000000) >> 56);
        buffer_out[write_index++] = static_cast<char>((i & 0x00FF000000000000) >> 48);
        buffer_out[write_index++] = static_cast<char>((i & 0x0000FF0000000000) >> 40);
        buffer_out[write_index++] = static_cast<char>((i & 0x000000FF00000000) >> 32);
        buffer_out[write_index++] = static_cast<char>((i & 0x00000000FF000000) >> 24);
        buffer_out[write_index++] = static_cast<char>((i & 0x0000000000FF0000) >> 16);
        buffer_out[write_index++] = static_cast<char>((i & 0x000000000000FF00) >> 8);
        buffer_out[write_index++] = static_cast<char>((i & 0x00000000000000FF) >> 0);
    }

    file_out.write(buffer_out, COUNTS_SIZE);

    return counts;
}

std::vector<uint64_t> count(std::ifstream &file){

    std::vector<uint64_t> counts;
    counts.reserve(BYTE_SIZE);

    char buffer[2048];
    int index = 0;

    file.read(buffer, 2048);
    std::cout << "read " << file.gcount() << " bytes" << std::endl;
    auto *ubuffer = reinterpret_cast<unsigned char *>(buffer);
    while (index < 2048){
        uint64_t next = 0;
        next |=  static_cast<uint64_t>(static_cast<unsigned char>(buffer[index++])) << 56;
        next |=  static_cast<uint64_t>(static_cast<unsigned char>(buffer[index++])) << 48;
        next |=  static_cast<uint64_t>(static_cast<unsigned char>(buffer[index++])) << 40;
        next |=  static_cast<uint64_t>(static_cast<unsigned char>(buffer[index++])) << 32;
        next |=  static_cast<uint64_t>(static_cast<unsigned char>(buffer[index++])) << 24;
        next |=  static_cast<uint64_t>(static_cast<unsigned char>(buffer[index++])) << 16;
        next |=  static_cast<uint64_t>(static_cast<unsigned char>(buffer[index++])) << 8;
        next |=  static_cast<uint64_t>(static_cast<unsigned char>(buffer[index++])) << 0;
        counts.emplace_back(next);
    }

    return counts;
}

void tree_traverse(huffman_tree::tree *node1, huffman_tree::tree *node2){
    if (node1->value != node2->value){
        std::cout << "error" << std::endl;
    }
    if ( (node1->character == nullptr) != (node2->character == nullptr)){
        std::cout << "error" << std::endl;
    }
    if ( (node1->left == nullptr) != (node2->left == nullptr)){
        std::cout << "error" << std::endl;
    }
    if ( (node1->right == nullptr) != (node2->right == nullptr)){
        std::cout << "error" << std::endl;
    }
    if (node1->character and node2->character and *(node1->character) != *(node2->character)){
        std::cout << "error" << std::endl;
    }
    if( node1->left and node2->left){
        tree_traverse(node1->left, node2->left);
    };
    if (node1->right and node2->right){
        tree_traverse(node1->right, node2->right);
    }

}

int main(int argc, char *argv[]) {
    std::ifstream in;
    in.open("test_in/diverse.txt", std::ios::in|std::ios::binary);
    std::ofstream huff;
    huff.open("test_huff/diverse.huff", std::ios::out|std::ios::binary);

    auto counts1 = count(in, huff);

    in.close();
    huff.close();

    std::ifstream huff2;
    huff2.open("test_huff/diverse.huff", std::ios::in|std::ios::binary);
    auto counts2 = count(huff2);
    huff2.close();

    auto hufft1 = huffman_tree(counts1);
    auto hufft2 = huffman_tree(counts2);

    tree_traverse(hufft1.root, hufft2.root);

    return 0;
}