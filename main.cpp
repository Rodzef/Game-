#include "FiveWindow.hpp"

int main() {
    FiveWindow window(500 / 4, 4, "15!!!.jpg");
    window.shuffle();
    window.run();
	return 0;
}