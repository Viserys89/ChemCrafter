// display.cpp
#include <cstdlib>
using namespace std;

void clearScreen() {
#ifdef _WIN32
    system("cls"); // Untuk Windows
#else
    system("clear"); // Untuk Linux / MacOS
#endif
}
