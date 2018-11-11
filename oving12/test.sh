#!/usr/bin/env sh

rm -r cmake/*
cd cmake
cmake .. > /dev/null
make > /dev/null || make
cd ..

rm test_huff/* test_out/*

for file in test_in/*
do
    cmake/compress ${file} test_huff > /dev/null
done

for file in test_huff/*
do
    cmake/decompress ${file} test_out > /dev/null
done

cd test_in
for file in *
do
    cmp -b ${file} ../test_out/${file}
done
