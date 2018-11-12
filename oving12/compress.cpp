#define BOOST_FILESYSTEM_VERSION 3

#include <iostream>
#include <fstream>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>
#include "huffman_tree.hpp"
#include "constants.hpp"

long COUNTS_SIZE;

std::vector<uint64_t> count(std::ifstream &file_in, std::ofstream &file_out){

    file_in.clear();
    file_in.seekg(0);

    file_out.clear();
    file_out.seekp(0);

    std::vector<uint64_t> counts;
    counts.reserve(BYTE_SIZE);
    for (int i = 0; i < BYTE_SIZE; ++i) {
        counts.emplace_back(0);
    }

    char c;
    while (file_in.get(c)) {
        counts[static_cast<unsigned char>(c)]++;
    }

    file_in.clear();
    unsigned long bytecount_ending = file_in.tellg() & 0xFF;

    c = static_cast<char>(bytecount_ending);
    file_out.put(c);

    file_in.clear();
    file_in.seekg(0);

    unsigned int VAL_SIZE = 0; // largest nonzero sub-byte in counts.

    uint64_t val = *std::max_element(counts.begin(), counts.end()); // biggest value in counts

    for(unsigned int j = 0; j < 8; j++) {
        if ((val & (0xFF << (8 * j))) != 0) VAL_SIZE = j + 1; // find largest non-zero byte
    }
    file_out.put(static_cast<char>(VAL_SIZE));

    for(uint64_t i : counts){
        for(uint64_t j = 0; j < VAL_SIZE; j++){
            file_out.put(static_cast<char>((i & (0xFF << 8*j) ) >> 8*j));
        }
    }

    COUNTS_SIZE = 2 + VAL_SIZE*BYTE_SIZE; // 1 for ending + 1 for size + 256 frequencies * VAL_SIZE bytes per frequency

    return counts;
}

void huffman_encode(const huffman_tree &huffman, std::ifstream &file_in, std::ofstream &file_out){
    char buffer_read[BLOCK_SIZE];
    char buffer_write[BLOCK_SIZE];
    int write_index = 0;

    char buffer_bool = 0;
    char bit_index = 0;

    file_out.clear();
    file_out.seekp(COUNTS_SIZE);

    do{
        file_in.read(buffer_read, BLOCK_SIZE);
        if (verbose) std::cout << "read " << file_in.gcount() << " bytes" << std::endl;
        for(int i = 0; i < file_in.gcount(); i++){
            auto c  = static_cast<unsigned char>(buffer_read[i]);
            auto decisions = huffman.paths[c];
            for (bool d : decisions){
                //std::cout << d << std::endl;
                buffer_bool |= d << bit_index++;

                if (bit_index == 8){
                    buffer_write[write_index++] = buffer_bool;
                    buffer_bool = bit_index = 0;

                    if (write_index == BLOCK_SIZE){
                        file_out.write(buffer_write, BLOCK_SIZE);
                        if (verbose) std::cout << "wrote " << BLOCK_SIZE << " bytes" << std::endl;
                        write_index = 0;
                    }
                }
            }
        }
    } while (file_in.gcount() > 0);

    buffer_write[write_index++] = buffer_bool;
    file_out.write(buffer_write, write_index);

    if (verbose) std::cout << "wrote " << write_index+1 << " bytes" << std::endl; // +1 because put
}

int main(int argc, char *argv[]) {
    auto filename_in = test_in / boost::filesystem::path("compress.cpp");
    if(argc > 1) filename_in = argv[1];

    auto file_part = filename_in.stem();
    auto extension = filename_in.extension();

    auto filename_out = test_huff;
    if(argc > 2) filename_out = argv[2];
    if (boost::filesystem::is_directory(filename_out)){
        filename_out /= file_part;
        filename_out += extension;
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
