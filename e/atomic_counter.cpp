#include <iostream>
#include <thread>
#include <atomic>

std::atomic<int> global_counter(0);

void incrementCounter() {
    for (int i = 0; i < 1000; ++i) {
        ++global_counter;
    }
}

int main() {
    // Create two threads
    std::thread thread1(incrementCounter);
    std::thread thread2(incrementCounter);

    // Join the threads with the main thread
    thread1.join();
    thread2.join();

    // Print the final value of global_counter
    std::cout << "Final value of global_counter: " << global_counter << std::endl;

    return 0;
}

