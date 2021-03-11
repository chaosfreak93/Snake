#include <iostream>
#include <thread>
#include "Game.cpp"

using namespace std;

void ShutdownHook() {
    while (true) {
        if (GetAsyncKeyState(VK_RCONTROL) != 0) {
            exit(0);
        }
    }
}

int main() {
    string quest;
    cout << "Booting up..." << endl;
    Setup();
    cout << "Copyright Yan-Luca L." << endl;
    cout << "Walls? y/Y (default: false)" << endl;
    cin >> quest;
    if (quest == "y" || quest == "Y")
        walls = true;
    Sleep(100);
    thread draw_thread([] { return Draw(); });
    thread input_thread([] { return Input(); });
    thread logic_thread([] { return Logic(); });
    thread shutdown_thread([] { return ShutdownHook(); });

    draw_thread.join();
    input_thread.join();
    logic_thread.join();
    shutdown_thread.join();

    return 0;
}
