
2 separate files in same a computer are sharing data. Using shm_open and semaphore.

consume.cpp and product.cpp are 2 separate processes which syncs time. Product.cpp sends time to consume.cpp.
//compile: 
g++ product.cpp -o product.out -std=c++11 -lpthread -lrt
g++ consume.cpp -o consume.out -std=c++11 -lpthread -lrt


Camera_product.cpp and Camera_consume.cpp are 2 separate prcesses sync images. Camera_product.cpp captures an array images and sends it to Camera_consume.cpp. To do it, Camera_product.cpp not display frame on screen save some milliseconds. it helps speed up frame rate. Camera_consume.cpp is displayed what camera captures. 
//compile: 
g++ Camera_product.cpp -o Camera_product.out -std=c++11 -lpthread -lrt `pkg-config opencv --cflags --libs
g++ Camera_consume.cpp -o Camera_consume.out -std=c++11 -lpthread -lrt `pkg-config opencv --cflags --libs`