
//apply mutual exclusion (mutex) a special case of the semaphore.
// 2 threads will access to one resource.
// mutex makes sure that only 1 thread can access to that resource by lock and unclock. 
// when thread1 is done, it signal to thread2. 
//  thread2 is waiting to that signal. 

// This code show that how 2 threads can access to 1 number. 2 threads increase that number and each thread prints out even or odd number. 
// also, it shows that how can you pass reference parameter to thread using std::ref.


#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>

std::mutex my_mutex;
bool ready = false;
std::condition_variable thread_ready;

void thread1(int &number){
    while(number < 100){
        std::unique_lock<std::mutex> my_lock(my_mutex);
        thread_ready.wait(my_lock,[]{return (!ready);});
        std::cout << "even number: " << number << std::endl;
        number++;
        ready = true;
        thread_ready.notify_one();
    }
    return;
}

void thread2(int &number){
    while(number < 100){
        std::unique_lock<std::mutex> my_lock(my_mutex);
        thread_ready.wait(my_lock,[]{return(ready);});
        std::cout << "odd number:     " << number << std::endl;
        number++;
        ready = false;
        thread_ready.notify_one();
    }
    return;
}

int main(){
    int number = 0;
    std::thread t1(thread1,std::ref(number));
    std::thread t2(thread2, std::ref(number));

    t1.join();
    t2.join();
    return 0;
}