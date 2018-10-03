#include "Application2D.h"

int main() {
	
	auto app = new Application2D();
	app->run("Physics 2D Test Environment", 1280, 720, false);
	delete app;

	return 0;
}