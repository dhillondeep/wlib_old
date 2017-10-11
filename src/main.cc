#include "Wlib.h"
#include <Serial/SerialStream.h>

using namespace wlp;

int freeRam () {
	extern int __heap_start, *__brkval;
	int v;
	return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}


void setup() {
	serialstream.start(9600);
	cout << "Feed me an integers." << endl;
}

void loop() {
	string val = string{"hello"};
	cout << freeRam() << endl;
}