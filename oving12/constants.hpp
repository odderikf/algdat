//
// Created by odderikf on 11/10/18.
//

#ifndef OVING12_CONSTANTS_HPP
#define OVING12_CONSTANTS_HPP

#include <boost/filesystem.hpp>

const int BYTE_SIZE = 256;
const int BLOCK_SIZE = 8192;
const int COUNTS_SIZE = 2048;

const boost::filesystem::path test_in("test_in");
const boost::filesystem::path test_out("test_out");
const boost::filesystem::path test_huff("test_huff");
const boost::filesystem::path huff("huff");
const boost::filesystem::path dot(".");

const bool verbose = false;

#endif //OVING12_CONSTANTS_HPP
