#!/bin/bash


function pause(){
   read -p "$*"
}


cd ..
cppcheck --enable=all --language=c tf_idf_lib/include/*.h tf_idf_lib/source/*.c --suppress=missingInclude
pause 'Press [Enter] key to continue...'

cpplint --extensions=c tf_idf_lib/include/* tf_idf_lib/source/*
pause 'Press [Enter] key to continue...'

mkdir build && cd build
cmake ..  

make clean && make
pause 'Press [Enter] key to continue...'

valgrind --tool=memcheck --leak-check=full ctest
pause 'Press [Enter] key to continue...'