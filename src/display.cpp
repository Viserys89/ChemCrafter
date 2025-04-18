#include <cstdlib>

void clearScreen() {
#ifdef _WIN32
    system("cls"); // Untuk Windows
#else
    system("clear"); // Untuk Linux / MacOS
#endif
}
