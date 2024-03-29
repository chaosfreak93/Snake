#include <algorithm>
#include <iostream>
#include <thread>
#include <string>
#include "Game.cpp"

using namespace std;

int main() {
    string quest;
    cout.setf(ios::unitbuf);
    cout << "Booting up..." << endl;
    Setup();
    cout << "Copyright Yan-Luca L." << endl;
    cout << "Walls? y/n (default: n)" << endl;
    cin >> quest;
    transform(quest.begin(), quest.end(), quest.begin(), ::tolower );
    if (quest == "y")
        walls = true;
    else
        walls = false;
    cout << "W = Up; A = Left; S = Down; D = Right; X = Game Over; Game start in 1Second" << endl;
    Sleep(1000);
    thread draw_thread([] { return Draw(); });
    thread input_thread([] { return Input(); });
    thread logic_thread([] { return Logic(); });

    draw_thread.join();
    input_thread.join();
    logic_thread.join();

    return 0;
}
