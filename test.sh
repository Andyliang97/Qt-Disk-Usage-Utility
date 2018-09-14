#! /bin/bash

export CPPLIBS=/home/junjie/Desktop/ECE3574/hw3/sumbit/qtproject/
export LD_LIBRARY_PATH=${CPPLIBS}:${LD_LIBRARY_PATH}

cd argulist 
qmake 
make 
cd ..

cd diskusage 
qmake 
make 
cd ..

cd testdiskusage 
qmake 
make 
cd ..

