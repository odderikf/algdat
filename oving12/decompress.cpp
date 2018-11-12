#define BOOST_FILESYSTEM_VERSION 3

#include <iostream>
#include <fstream>
#include <vector>
#include "huffman_tree.hpp"
#include <boost/filesystem.hpp>
#include "constants.hpp"

long COUNTS_SIZE;
std::vector<uint64_t> count(std::ifstream &file){

    std::vector<uint64_t> counts;
    counts.reserve(BYTE_SIZE);

    char buffer[2049]; // worst case size
    int index = 0;

    file.read(buffer, 2049);
    int VAL_SIZE = static_cast<int>(static_cast<unsigned char>(buffer[index++]));

    if (verbose) std::cout << "read " << file.gcount() << " bytes" << std::endl;
    auto *ubuffer = reinterpret_cast<unsigned char *>(buffer);
    //std::cerr << VAL_SIZE << " " << VAL_SIZE*32 << std::endl;
    for (int counter = 0; counter < BYTE_SIZE; counter++){
        uint64_t next = 0;
        for(int i = 0; i < VAL_SIZE; i++){
            next |=  static_cast<uint64_t>(ubuffer[index++]) << (i*8);
        }

        counts.emplace_back(next);
    }
    COUNTS_SIZE = index;

    return counts;
}

void huffman_decode(const huffman_tree &huffman, std::ifstream &file_in, std::ofstream &file_out){

    char buffer_write[BLOCK_SIZE];
    int write_index = 0;

    char buffer_bool = 0;

    huffman_tree::tree *position = huffman.root;

    file_in.seekg(COUNTS_SIZE-1);
    file_in.clear();

    char temp;
    file_in.get(temp);
    long bytecount_ending = static_cast<long>(static_cast<unsigned char>(temp));

    while(file_in.get(buffer_bool)) {
        /*if (file_in.eof() and i == file_in.gcount()){ // todo make this work :&
            max_bit_index -= static_cast<unsigned char>(bits_to_skip);
        }*/
        for(signed int i = 0; i < 8; ++i){
            bool direction = static_cast<bool>((buffer_bool >> i) & 1);
            if ( direction == huffman_tree::LEFT){
                position = position->left;
            } else if (direction == huffman_tree::RIGHT){
                position = position->right;
            }

            if (position->character != nullptr){
                buffer_write[write_index++] = *(position->character);
                position = huffman.root;

                if (write_index == BLOCK_SIZE) {

                    while (bytecount_ending != (( (int)file_out.tellp() + write_index ) & 0xFF) ){
                        write_index--;
                        // hack to fix bug caused by a byte having garbage data at end
                        // should ideally be fixed by saving the amount of bits that do not count
                        // and not parsing them, but can't get it to work :/
                    }
                    file_out.write(buffer_write, BLOCK_SIZE);
                    if (verbose) std::cout << "wrote " << BLOCK_SIZE << " bytes" << std::endl;
                    write_index = 0;
                }
            }

        }
    }


    while (bytecount_ending != (( (int)file_out.tellp() + write_index ) & 0xFF) ){
        write_index--; // hack to fix bug, see above
    }
    file_out.write(buffer_write, write_index);
    if (verbose) std::cout << "wrote " << write_index << " bytes" << std::endl;
}

int main(int argc, char *argv[]) {
    auto filename_in = test_huff / boost::filesystem::path("compress.cpp.huff");
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
