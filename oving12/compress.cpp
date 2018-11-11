#define BOOST_FILESYSTEM_VERSION 3

#include <iostream>
#include <fstream>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/filesystem.hpp>
#include "huffman_tree.hpp"
#include "constants.hpp"

std::vector<uint64_t> count(std::ifstream &file_in, std::ofstream &file_out){

    file_in.seekg(0);
    file_in.clear();

    std::vector<uint64_t> counts;
    counts.reserve(BYTE_SIZE);
    for (int i = 0; i < BYTE_SIZE; ++i) {
        counts.emplace_back(0);
    }

    unsigned int VAL_SIZE = 0; // largest nonzero bit-octuple in counts.

    char c;
    while (file_in.get(c)) {
        counts[static_cast<unsigned char>(c)]++;
    }

    for(unsigned int i = 0; i < BYTE_SIZE; ++i){
        uint64_t val = counts[i];
        unsigned int size = 0;
        for(unsigned int j = 1; i < 9; i++){
            if( val & 0xF << j) size = j; // find largest non-zero byte
        }

        if(val > VAL_SIZE) VAL_SIZE = size;
    }

    //file_out.put(static_cast<char>(VAL_SIZE));

    for(uint64_t i : counts){
        for(uint64_t j = 7/*VAL_SIZE-1*/; j != UINT64_MAX; j--){ // from 7 to 0, except you might get to store less than 8 bytes per value
            file_out.put(static_cast<char>((i & (0xFF << 8*j) ) >> 8*j));
        }
    }

    return counts;
}

void huffman_encode(const huffman_tree &huffman, std::ifstream &file_in, std::ofstream &file_out){
    char buffer_read[BLOCK_SIZE];
    char buffer_write[BLOCK_SIZE];
    int write_index = 0;

    char buffer_bool = 0;
    char bit_index = 0;

    file_in.clear();
    file_in.seekg(0);

    file_out.clear();
    file_out.seekp(COUNTS_SIZE+1);

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

    file_out.clear();
    file_out.seekp(COUNTS_SIZE);
    //file_out.put(bit_index);
    file_in.seekg(0, std::ios::end);
    file_in.clear();
    long bytecount_ending = file_in.tellg() & 0xFF;

    char c = static_cast<char>(bytecount_ending);
    file_out.put(c);

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
