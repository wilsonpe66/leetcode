#include <iostream>
#include <thread>
#include <atomic>

std::atomic<int> lock(0); // 0 means unlocked, 1 means locked
int shared_resource = 0;

void criticalSection() {
    // Acquire the lock
    while (lock.exchange(1, std::memory_order_acquire) == 1) {
        // Another thread is holding the lock, spin until it's released
    }

    // Critical section: manipulate the shared resource
    ++shared_resource;

    // Release the lock
    lock.store(0, std::memory_order_release);
}

int main() {
    // Create two threads
    std::thread thread1(criticalSection);
    std::thread thread2(criticalSection);

    // Join the threads with the main thread
    thread1.join();
    thread2.join();

    // Print the final value of shared_resource
    std::cout << "Final value of shared_resource: " << shared_resource << std::endl;

    return 0;
}

