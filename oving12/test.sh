#!/usr/bin/env bash

rm -r cmake/*
cd cmake
cmake ..
make
cd ..

rm test_huff/* test_out/*

for file in test_in/*
do
    cmake/compress ${file} test_huff
done

for file in test_huff/*
do
    cmake/decompress ${file} test_out
done

cd test_in
for file in *
do
    cmp -b ${file} ../test_out/${file}
done
