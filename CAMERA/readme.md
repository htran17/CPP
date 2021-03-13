
it needs an opencv3 package.

how to compile

g++ ClassCamera.cpp -o ClassCamera.out -std=c++11 -lpthread -lv4l2 -fopenmp -ltbb `pkg-config opencv --cflags --libs`
