
2 separate files in same a computer are sharing data. Using shm_open and semaphore. 
//compile: g++ product.cpp -o product.out -std=c++11 -lpthread -lrt
	   g++ consume.cpp -o consume.out -std=c++11 -lpthread -lrt
