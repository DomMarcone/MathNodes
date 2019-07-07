//MathNodesTest.cpp
#include "MathNodes.hpp"
#include "MathTreeBuilder.hpp"

#include <stdio.h>
#include <time.h>

#include <math.h>

#define MAX_BUFFER_SIZE 128

float time_func();
float exit_func();


int main(int argc, char **args){
	char temp[MAX_BUFFER_SIZE];
	float pi = 3.14159265359;
	
	MathTreeBuilder mtb;
	
	mtb.addVariable(&pi, "pi");
	
	mtb.addFunction(time_func,"time");
	mtb.addFunction(exit_func,"exit");
	
	//addFunction is overloaded to handle both:
	//	float (*func)()
	//	float (*func)(float)
	mtb.addFunction(sinf,"sin");
	mtb.addFunction(cosf,"cos");
	mtb.addFunction(tanf,"tan");
	
	while(true){
		MathNode *mn;
		printf(">");
		gets(temp);
		mn = mtb.parse(temp);
		printf(" %f\n\n", mn->getValue());
		delete mn;
	}
	
	return 0;
}


float time_func(){ return clock()/1000.f; }

float exit_func(){
	exit(0);
	return 0.f;
}
