#include <iostream>
#include <chrono>
#include <thread>
using namespace std;
using namespace std::chrono;

void showTime(duration<double> elapsed) {
    int total_seconds = static_cast<int>(elapsed.count());
    int hours = total_seconds / 3600;
    int minutes = (total_seconds % 3600) / 60;
    int seconds = total_seconds % 60;

    cout << "\rElapsed Time: "
         << (hours < 10 ? "0" : "") << hours << ":"
         << (minutes < 10 ? "0" : "") << minutes << ":"
         << (seconds < 10 ? "0" : "") << seconds
         << flush;
}

int main() {
    bool running = false;
    auto start_time = steady_clock::now();
    duration<double> total_time{0};

    while (true) {
        cout << "\n\nStopwatch Menu:\n";
        cout << "1. Start\n2. Stop\n3. Reset\n4. Exit\n";
        cout << "Choose an option: ";

        int choice;
        cin >> choice;

        if (choice == 1 && !running) {
            running = true;
            start_time = steady_clock::now();
            cout << "Stopwatch started...\n";

            while (running) {
                auto current = steady_clock::now();
                auto elapsed = total_time + (current - start_time);
                showTime(elapsed);
                this_thread::sleep_for(seconds(1));

                // Check if user pressed Enter to stop
                if (cin.rdbuf()->in_avail() > 0) {
                    break;
                }
            }
        } else if (choice == 2 && running) {
            total_time += steady_clock::now() - start_time;
            running = false;
            cout << "\nStopwatch paused.\n";
        } else if (choice == 3) {
            total_time = duration<double>(0);
            running = false;
            cout << "\nStopwatch reset.\n";
        } else if (choice == 4) {
            break;
        } else {
            cout << "Invalid option.\n";
        }
    }

    return 0;
}
