#include "FiveWindow.h"

int main() {
	FiveWindow window(500/4, 4, "images/15!!!.jpg");
	window.shuffle();
	window.run();
	return 0;
}