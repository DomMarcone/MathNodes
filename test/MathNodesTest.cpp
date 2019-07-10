//MathNodesTest.cpp
#include "MathNodes.hpp"
#include "MathTreeBuilder.hpp"

#include <stdio.h>

#define _USE_MATH_DEFINES
#include <math.h>

#define MAX_BUFFER_SIZE 128

float exit_func();

int main(int argc, char **args){
	char temp[MAX_BUFFER_SIZE];
	float pi = 3.14159265359f;
	
	MathTreeBuilder mtb;
	MathNode *mn;
	
	mtb.addVariable(&pi, "pi");
	
	mtb.addFunction(exit_func,"exit");
	
	//addFunction is overloaded to handle both:
	//	float (*func)()
	//	float (*func)(float)
	mtb.addFunction(sinf,"sin");
	mtb.addFunction(cosf,"cos");
	mtb.addFunction(tanf,"tan");
	
	while(true){
		printf("expression : ");
		gets_s(temp);
		mn = mtb.parse(temp);
		printf("\t%f\n\n", mn->getValue());
		delete mn;
	}
	
	return 0;
}


float exit_func(){
	exit(0);
	return 0.f;
}
