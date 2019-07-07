//iparse.cpp
/*******************************************************
**                                                    **
** Inline parser for batch floating point opperations **
**                                                    **
*******************************************************/

#include "MathTreeBuilder.hpp"
#include "MathNodes.hpp"

#include <stdio.h>
#include <string.h>

#include <cmath>

#define PARSER_BUFFER 256
#define INPUT_BUFFER 64

void loadMath(MathTreeBuilder*);

enum Mode {
	BINARY_MODE,
	STRING_MODE
};

int main( int argc, char *argv[]){
	MathTreeBuilder mtb;
	MathNode *mn = 0;
	
	Mode current_mode = BINARY_MODE;
	
	//increments with each itteration
	float count = 0.f;
	
	//use input and output variables
	float input, output;
	mtb.addVariable(&input,"input");
	
	mtb.addVariable(&count,"count");
	
	//shoud we begin parsing, or was there an argument error?
	bool run = true;
	
	FILE *in = stdin, *out = stdout;
	
	//handle arguments
	for(int i=1; i<argc-1; ++i){
		
		//help
		if(strcmp(argv[i],"-h")==0 || strcmp(argv[i],"--help")==0){
			printf("Usage: iparse [options] \"parsable string\"\n");
			printf("Options:\n");
			printf("  -b, --binary\tInput and output are binary floating point values. (default)\n");
			printf("  -i, --input\tSet input to file. If ignored, stdin will be used.\n");
			printf("  -o, --output\tSet output to file. If ignored, stdout will be used.\n");
			printf("  -s, --string\tInput and output are strings, representing floating point values.\n");
			
			printf("\nCompiled on %s %s.\n",__DATE__,__TIME__);
			run = false;
		}
		
		
		//binary mode
		if(strcmp(argv[i],"-b")==0 || strcmp(argv[i],"--binary")==0){
			current_mode = BINARY_MODE;
		}
		
		//string mode
		if(strcmp(argv[i],"-s")==0 || strcmp(argv[i],"--string")==0){
			current_mode = STRING_MODE;
		}
		
		//input
		if(strcmp(argv[i],"-i")==0 || strcmp(argv[i],"--input")==0){
			in = fopen(argv[++i],"rb");
			
			if(in==0){
				printf("Error reading from %s\n",argv[i]);
				exit(1);
			}
		}
		
		//output
		if(strcmp(argv[i],"-o")==0 || strcmp(argv[i],"--output")==0){
			in = fopen(argv[++i],"ab+");
			
			if(in==0){
				printf("Error writing to %s\n",argv[i]);
				exit(1);
			}
		}
		
	}
	
	//parse final token
	if(argc>1){
		loadMath(&mtb);
		mn = mtb.parse(argv[argc-1]);
	} else {
		printf("Usage: iparse [options] \"parsable string\"\n");
		printf("Try 'iparse --help' for more information.\n");
		exit(1);
	}
	
	while(run){
		if(!feof(in)){
			if(current_mode == BINARY_MODE){
				fread(&input,sizeof(float),1,in);
				output = mn->getValue();
				fwrite(&output,sizeof(float),1,out);
				
			} else if(current_mode == STRING_MODE){
				int i = fscanf(in,"%f",&input);
				if(i!=1){
					printf("Error parsing input value!\n");
					exit(1);
				}
				output = mn->getValue();
				fprintf(out,"%f\n",output);
				
			}
			
			count += 1.f;
		} else {
			run=false;
		}
	}
	
	if(in != stdin)fclose(in);
	if(out != stdout)fclose(out);
	delete mn;
	return 0;
}


float func_log(float i){return (float)log(i);}
float func_log2(float i){return (float)log2(i);}
float func_log10(float i){return (float)log10(i);}

float func_abs(float i){return i>0 ? i : -i;}

void loadMath(MathTreeBuilder *m){
	static float pi = M_PI;
	static float e = M_E;
	
	m->addFunction(sinf,"sin");
	m->addFunction(cosf,"cos");
	m->addFunction(tanf,"tan");
	
	m->addFunction(asinf,"asin");
	m->addFunction(acosf,"acos");
	m->addFunction(atanf,"atan");
	
	m->addFunction(func_log,"log");
	m->addFunction(func_log2,"log2");
	m->addFunction(func_log10,"log10");
}
