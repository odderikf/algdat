#define BOOST_FILESYSTEM_VERSION 3

#include <iostream>
#include <fstream>
#include <vector>
#include "huffman_tree.hpp"
#include <boost/filesystem.hpp>
#include "constants.hpp"

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

int main(int argc, char *argv[]) {
    auto filename_in = test_huff / boost::filesystem::path("opg12.tex.huff");
    if(argc > 1) filename_in = argv[1];

    auto file_part = filename_in.stem();
    auto extension = filename_in.extension();

    auto filename_out = test_out / filename_in;
    if(argc > 2) filename_out = argv[2];
    if (boost::filesystem::is_directory(filename_out)){
        filename_out /= file_part;
    }

    std::ifstream file_in;
    std::ofstream file_out;

    file_in.open(filename_in.string()  , std::ios::in  | std::ios::binary);
    file_out.open(filename_out.string(), std::ios::out | std::ios::binary);

    std::vector<uint64_t> counts = count(file_in);

    auto huff = huffman_tree(counts);

    huffman_decode(huff, file_in, file_out);

    file_in.close();
    file_out.close();
    return EXIT_SUCCESS;
}
