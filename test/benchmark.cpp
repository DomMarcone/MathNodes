//optimizer.cpp
#include "MathNodes.hpp"
#include "MathTreeBuilder.hpp"

#include <stdio.h>
#include <time.h>


#define _USE_MATH_DEFINES
#include <math.h>


//a simple string designed to test multiple operations
#define TEST_STRING "2.71828^(pi%2+42-sin(3.3333)*input)"

#define TEST_COUNT 1000000

/*
TODO:
	Make the benchmark took extensible, with command line
options to set the string and itteration count.
*/


int main(int argc, char *argv[]){
	MathTreeBuilder mtb;
	MathNode *mn;
	float input;
	clock_t end, initial, control, start = clock();
	
	mtb.addFunction(sinf,"sin");
	mtb.addFunction(cosf,"cos");
	mtb.addFunction(tanf,"tan");
	
	mtb.addVariable(&input,"input");
	
	mn = mtb.parse(TEST_STRING);
	
	initial = clock();
	
	//do a control test to compare to
	for(int i=0; i<TEST_COUNT; ++i){
		input = rand();
	}
	
	control = clock();
	
	for(int i=0; i<TEST_COUNT; ++i){
		input=rand();
		mn->getValue();
	}
	
	end = clock();
	
	printf("Benchmark results:\n");
	printf("\tinitialization:\t%dms\n",initial-start);
	printf("\tcontrol:\t%dms\n",control-initial);
	printf("\ttest:\t\t%dms\n",end-control);
	printf("\ttest-control:\t%dms\n",(end-control)-(control-initial));
	
	//to avoid memory leakage
	delete mn;
	
	return 0;
}

