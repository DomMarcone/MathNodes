//parse.cpp
#include "MathNodes.hpp"
#include "MathTreeBuilder.hpp"

#include <stdio.h>
#include <time.h>

#define _USE_MATH_DEFINES
#include <math.h>

#define MAX_BUFFER_SIZE 128

float help_func();
float time_func();
float exit_func();


int main(int argc, char **args){
	char temp[MAX_BUFFER_SIZE];
	float pi = 3.14159265359;
	float e = 2.7182818284;
	
	float count = 0;
	
	MathTreeBuilder mtb;
	
	mtb.addVariable(&pi, "pi");
	mtb.addVariable(&e, "e");
	mtb.addVariable(&count, "count");
	
	mtb.addFunction(time_func,"time");
	mtb.addFunction(help_func,"help");
	mtb.addFunction(exit_func,"exit");
	
	mtb.addFunction(sinf,"sin");
	mtb.addFunction(cosf,"cos");
	mtb.addFunction(tanf,"tan");
	
	mtb.addFunction(asinf,"asin");
	mtb.addFunction(acosf,"acos");
	mtb.addFunction(atanf,"atan");
		
	//mtb.addFunction(sqrtf,"sqrt"); //removed. Please use "^0.5"
	
	while(true){
		MathNode *mn;
		printf(">");
		gets_s(temp);
		mn = mtb.parse(temp);
		printf(" %f\n\n", mn->getValue());
		
		delete mn;
		count += 1.f;
	}
	
	return 0;
}


float time_func(){ return clock()/1000.f; }

float help_func(){
	printf(" Mathmatical parser which works recursively\n");
	printf(" on substrings. This is only a test.\n");
	printf(" Currently supported functions :\n");
	printf("\thelp()\t-prints this\n");
	printf("\ttime()\t-returns time in seconds\n");
	printf("\texit()\t-exits the parser\n");
	printf("\tsin(theta)\n");
	printf("\tcos(theta)\n");
	printf("\ttan(theta)\n");
	printf("\tasin(theta)\n");
	printf("\tacos(theta)\n");
	printf("\tatan(theta)\n");
	printf("\n");
	return 1.f;
}

float exit_func(){
	exit(0);
	return 0.f;
}
