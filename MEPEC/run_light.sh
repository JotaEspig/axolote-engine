cd ../tests/
mv main.cpp _main.cpp
mv light.cpp main.cpp
cd ..
cmake .
make clean
make -j4
./tests/bin/tests
cd tests
mv main.cpp light.cpp
mv _main.cpp main.cpp
cd ../MEPEC
