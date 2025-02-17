// author: prisha sujin kumar
// class for main

// -- include statements --
// third party libraries
// std libraries
// our libraries
#include "Program.hpp"
// -- end of include statements -- 

void loop() {}

int main(int argc, char** argv) {
	Program myProgram(1280, 720);
	// run !
	myProgram.SetLoopCallback(loop);
	
	return 0;
}
