// C64.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <iostream>
#include "C64.h"
#include "WaveGenerator.h"

#define DEBUG 0

int main(int argc, char* argv[])
{

	C64 theC64;
	//theC64.run();
    theC64.test();
	soundTest();
    
	int a;
	std::cin >> a;
	return 0;
}

void soundTest(){
	int duration = 1000;
	double Hz = 440;

	WaveGenerator wg;
	wg.playSound(Hz, duration);
	wg.wait();
}