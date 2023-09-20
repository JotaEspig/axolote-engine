cd ..
cmake .
make clean
make -j4
./tests/bin/tests
cd MEPEC
