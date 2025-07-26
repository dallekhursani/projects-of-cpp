#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <ctime>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void clockWatch() {
    while (true) {
        clearScreen();

        // Get current time
        auto now = std::chrono::system_clock::now();
        std::time_t currentTime = std::chrono::system_clock::to_time_t(now);
        std::tm* localTime = std::localtime(&currentTime);

        // Display clock
        std::cout << "\n";
        std::cout << "      ⏰ Clock Watch ⏰\n";
        std::cout << "  -----------------------\n";
        std::cout << "        " 
                  << std::put_time(localTime, "%H:%M:%S") 
                  << "\n";
        std::cout << "  -----------------------\n";

        // Wait for 1 second
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

int main() {
    try {
        clockWatch();
    } catch (...) {
        std::cerr << "Clock stopped.\n";
    }
    return 0;
}
