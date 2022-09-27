#include "Application3D.h"

int main() {
	
	// allocation
	auto app = new Application3D();

	// initialise and loop
	app->run("Computer Graphics - Charlie O'Regan", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}