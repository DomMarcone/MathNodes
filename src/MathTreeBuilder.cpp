//MathTreeBuilder.cpp

#include "MathNodes.hpp"
#include "MathTreeBuilder.hpp"
#include "parenthesize.h"

#include <string.h>
#include <stdlib.h>

#include <string>
#include <vector>

MathNode * opToNode(char op, MathNode *left, MathNode *right);

MathNode *MathTreeBuilder::parse(char *input){
	return parseSub(0, strlen(input), input);
}

#ifdef MATH_TREE_VERBOSITY
	#include <stdio.h>

	void printSegment(size_t start, size_t end, char *input){
		printf("~");
		for(int i=0;i<start;++i)printf(" ");
		for(int i=start;i<end;++i)printf("%c",input[i]);
		//fill until the end of the line
		for(int i=end;input[i];++i)printf(" ");
	}
#endif //MATH_TREE_VERBOSITY

MathNode *MathTreeBuilder::parseSub(size_t start, size_t end, char *input){
	
	//are there unclosed/open parenthesises
	if(unclosed_parenthesis(start,end,input) != 0){
		#ifdef MATH_TREE_VERBOSITY
			printSegment(start,end,input);
			printf(" : unclosed parenthesis!\n");
		#endif //MATH_TREE_VERBOSITY
		return new ErrorNode();
	}
	
	if(start==end){
		#ifdef MATH_TREE_VERBOSITY
			printSegment(start,end,input);
			printf(" : start == end!\n");
		#endif //MATH_TREE_VERBOSITY
		return new ErrorNode();
	}
	
	//handle numeric constants
	if(is_constant(start,end,input)){
		int len = end-start+1;
		float value;
		char * temp = (char*)malloc(sizeof(char) * len);
		memcpy(temp,&input[start],len*sizeof(char));
		temp[len-1] = 0;
		
		value = atof(temp);
		free(temp);
		
		#ifdef MATH_TREE_VERBOSITY
			printSegment(start,end,input);
			printf(" : found constant %f\n", value);
		#endif //MATH_TREE_VERBOSITY
		
		return new ConstantNode(value);
	}
	
	//handle parenthesized regions
	if(is_parenthesized(start,end,input)){
		move_into_parenthesis(&start,&end,input);
		
		#ifdef MATH_TREE_VERBOSITY
			printSegment(start,end,input);
			printf(" : moved into parenthesis\n");
		#endif //MATH_TREE_VERBOSITY
		
		return parseSub(start,end,input);
	}
	
	//handle user-defined variables
	if(is_name(start,end,input)){
		size_t len = end-start+1;
		MathNode *temp;
		char *name = (char*)malloc(sizeof(char)*len);
		memcpy(name,&input[start],len*sizeof(char));
		name[len-1] = 0;
		temp = getVariable(name);
		
		#ifdef MATH_TREE_VERBOSITY
			printSegment(start,end,input);
			printf(" : variable %s\n",name);
		#endif //MATH_TREE_VERBOSITY
		
		free(name);
		
		if(temp!=0)return temp;
	}
	
	//handle user-defined functions (one param)
	if(is_function(start,end,input)){
		size_t len = 0;
		Function1ParamNode *temp;
		
		//shave off parenthesis
		while(input[start+len]!='(')len++;
		len++;
		
		char *name = (char*)malloc(sizeof(char)*len);
		memcpy(name,&input[start],len*sizeof(char));
		name[len-1] = 0;
		
		temp = getFunction1Param(name);
		
		#ifdef MATH_TREE_VERBOSITY
			printSegment(start,end,input);
			printf(" : function %s\n",name);
		#endif //MATH_TREE_VERBOSITY
		
		free(name);
		
		if(temp!=0){
			size_t l = get_next_char(start,end,'(',input), r = end;
			MathNode *mn = temp;
			
			move_into_parenthesis(&l,&r,input);
			temp->addParam(parseSub(l,r,input));
			return mn;
		}
	}
	
	//handle user-defined functions (no params)
	if(is_function(start,end,input)){
		size_t len = end-start;
		MathNode *temp;
		
		//shave off parenthesis
		while(input[start+len]!='(')len--;
		len++;
		
		char *name = (char*)malloc(sizeof(char)*len);
		memcpy(name,&input[start],len*sizeof(char));
		name[len-1] = 0;
		
		temp = getFunction(name);
		
		#ifdef MATH_TREE_VERBOSITY
			printSegment(start,end,input);
			printf(" : function %s\n",name);
		#endif //MATH_TREE_VERBOSITY
		
		free(name);
		
		if(temp!=0)return temp;
	}
	
	//handle simple math operators (possibly needs deprication)
	/*
	if(is_simple_math(start,end,input)){
		char op = get_math_operator_from_left(start,end,input);
		size_t l_end, r_start;
		MathNode *left, *right;
		l_end = get_left_token(start,end,input);
		r_start = get_right_token(start,end,input);
		
		if(l_end == -1 || r_start == -1)return new ErrorNode();
		
		#ifdef MATH_TREE_VERBOSITY
			printSegment(start,end,input);
			printf(" : simple math function\n");
		#endif
		
		left = parseSub(start,l_end,input);
		right = parseSub(r_start,end,input);
		
		return opToNode(op,left,right);
	}*/

	
	//if we've made it here, split the problem into smaller parts
	{
		char op = get_math_operator_from_left(start,end,input);
		if(!is_operator(op)){
			op = get_math_operator_from_right(start,end,input);
		} else if(!is_operator(op)){
			return new ErrorNode();
		}
		
		size_t l_end, r_start;
		MathNode *left, *right;
		l_end = get_left_token(start,end,input);
		r_start = get_right_token(start,end,input);
	
		if(l_end == -1 || r_start == -1)return new ErrorNode();
		
		#ifdef MATH_TREE_VERBOSITY
			printSegment(start,end,input);
			printf(" : spliting and parsing sides\n");
		#endif //MATH_TREE_VERBOSITY
		
		left = parseSub(start,l_end,input);
		right = parseSub(r_start,end,input);
		
		return opToNode(op,left,right);
		
	}
	
	return new ErrorNode();
}


MathNode * opToNode(char op, MathNode *left, MathNode *right){
	switch(op){
	case '^' :
		return new ExponentNode(left,right);
		break;//redundant break statement
		
	case '/' :
		return new DivideNode(left,right);
		break;
		
	case '*' :
		return new MultiplyNode(left,right);
		break;
		
	case '-' :
		return new SubtractNode(left,right);
		break;
		
	case '+' :
		return new AddNode(left,right);
		break;
		
	case '%' :
		return new ModulusNode(left,right);
		break;
		
	default:
		return new ErrorNode();
		break;
	}
	return new ErrorNode();
}



void MathTreeBuilder::addVariable(float *f, const char *n){
	variable a;
	a.name = n;
	a.value_ptr = f;
	variables.push_back(a);
}

void MathTreeBuilder::addVariable(float *f, const std::string &n){
	addVariable(f, (char*)n.c_str());
}


void MathTreeBuilder::addFunction(float (*fp)(), const char *n){
	function a;
	a.name = n;
	a.func_ptr = fp;
	functions.push_back(a);
}

void MathTreeBuilder::addFunction(float (*fp)(), const std::string &n){
	addFunction(fp, (char*)n.c_str());
}


void MathTreeBuilder::addFunction1Param(float (*fp)(float), const char *n){
	function1param a;
	a.name = n;
	a.func_ptr = fp;
	function1params.push_back(a);
}

void MathTreeBuilder::addFunction1Param(float (*fp)(float), const std::string &n){
	addFunction1Param(fp, (char*)n.c_str());
}

//overload addFunction to handle Function1ParamNodes
void MathTreeBuilder::addFunction(float (*fp)(float), const char *n){
	addFunction1Param(fp,n);
}

void MathTreeBuilder::addFunction(float (*fp)(float), const std::string &n){
	addFunction(fp, (char*)n.c_str());
}


MathNode *MathTreeBuilder::getVariable(char *name){
	for(int i=0;i<variables.size();++i){
		if( strcmp(variables[i].name, name)==0 ){
			return new VariableNode( variables[i].value_ptr );
		}
	}
	//didn't find it...
	return 0;
}

MathNode *MathTreeBuilder::getFunction(char *name){
	for(int i=0;i<functions.size();++i){
		if( strcmp(functions[i].name, name)==0 ){
			return new FunctionNode( functions[i].func_ptr );
		}
	}
	return 0;
}

Function1ParamNode *MathTreeBuilder::getFunction1Param(char *name){
	for(int i=0;i<function1params.size();++i){
		if( strcmp(function1params[i].name, name)==0 ){
			return new Function1ParamNode( function1params[i].func_ptr );
		}
	}
	return 0;
}

