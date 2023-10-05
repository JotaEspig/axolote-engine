cd ../tests/
mv main.cpp _main.cpp
mv minecraft.cpp main.cpp
cd ..
cmake .
make clean
make -j4
./tests/bin/tests
cd tests
mv main.cpp minecraft.cpp
mv _main.cpp main.cpp
cd ../MEPEC

