#define BOOST_FILESYSTEM_VERSION 3

#include <iostream>
#include <fstream>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>
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

int main(int argc, char *argv[]) {
    auto filename_in = test_in / boost::filesystem::path("opg12.tex");
    if(argc > 1) filename_in = argv[1];

    auto file_part = filename_in.stem();
    auto extension = filename_in.extension();

    auto filename_out = test_huff;
    if(argc > 2) filename_out = argv[2];
    if (boost::filesystem::is_directory(filename_out)){
        filename_out /= file_part;
        filename_out.replace_extension(extension);
        filename_out += dot;
        filename_out += huff;
    }

    std::ifstream file_in;
    std::ofstream file_out;

    file_in.open(filename_in.string()  , std::ios::in  | std::ios::binary);
    file_out.open(filename_out.string(), std::ios::out | std::ios::binary);

    std::vector<uint64_t> counts = count(file_in, file_out);

    auto huff = huffman_tree(counts);

    huffman_encode(huff, file_in, file_out);

    file_in.close();
    file_out.close();
    return EXIT_SUCCESS;
}
