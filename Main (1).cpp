#include <iostream>
#include <thread>
#include <mutex>
#include <chrono>

int shared_data = 0;          
std::mutex mtx;               

void writer_thread() {
    for (int i = 1; i <= 5; i++) {
        mtx.lock();
        shared_data = i;
        std::cout << "Writer: wrote " << shared_data << std::endl;
        mtx.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

void reader_thread() {
    for (int i = 1; i <= 5; i++) {
        mtx.lock();
        std::cout << "Reader: read " << shared_data << std::endl;
        mtx.unlock();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    std::thread t1(writer_thread);
    std::thread t2(reader_thread);

    t1.join();
    t2.join();

    return 0;
}
