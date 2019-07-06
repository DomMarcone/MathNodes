//parenthasize.c
#include "parenthesize.h"

#include <string.h>
#include <stdlib.h>

int is_operator(char c){
	switch(c){
	case '^' :
	case '*' :
	case '/' :
	case '+' :
	case '-' :
	case '%' :
		return TRUE;
		break;
	}
	return FALSE;
}


int is_whitespace(char c){
	switch(c){
	case ' ' :
	case '\n' :
	case '\t' :
		return TRUE;
		break;
	}
	return 0;
}

int enumerate_precedence(char op){
	switch(op){
	case '^' :
		return 1000;
		break; // I'm aware it's redundant
	case '/' :
		return 300;
		break;
	case '%' :
		return 200;
		break;
	case '*' :
		return 100;
		break;
	case '+' :
		return 20;
		break;
	case '-' :
		return 10;
		break;
	}
	return -1;
}

size_t get_next_whitespace(size_t start, size_t end, char *input){
	for(int i = start; i < end; ++i){
		if(is_whitespace(input[i]))return i;
	}
	return -1;
}


int is_numeric(char c){
	switch(c){
	case '.' :
		return TRUE;
		break;
	}
	if( c>='0' && c<='9' )return 1;
	return FALSE;
}


int is_alphanumeric(char c){
	switch(c){
	case '_' :
	case '.' :
		return TRUE;
		break;
	}
	if( c>='a' && c<='z' )return TRUE;
	if( c>='A' && c<='Z' )return TRUE;
	if( c>='0' && c<='9' )return TRUE;
	return FALSE;
}

int is_alphanumericparenthetic(char c){
	if(is_alphanumeric(c))return TRUE;
	if(c==')' || c=='(')return TRUE;
	return FALSE;
}


int is_parenthesized( size_t start, size_t end, char *input){
	size_t open_parenthesis = 0;
	//int starts_with_parenthesis = 0;
	int i;
	
	while(is_whitespace(input[start]))start++;
	
	if(input[start] != '('){
		//doesn't start with an open parenthesis
		return FALSE;
	}
	
	for(i = start; i < end; ++i){
		if( input[i] == '(' )open_parenthesis++;
		if( input[i] == ')' )open_parenthesis--;
		
		//make sure we're not in the middle of an expression...
		if( open_parenthesis==0 && input[i] != ')')return FALSE;
	}
	
	//last non-whitespace character should be a ')'
	i = end-1;
	while(is_whitespace(input[i]))i--;
	if(input[i] != ')'){
		return FALSE;
	}
	
	if( open_parenthesis == 0)return TRUE;
	return FALSE;//unmatched parenthesis
}


int unclosed_parenthesis(size_t start, size_t end, char *input){
	int open_parenthesis = 0;
	for(int i = start; i<end; ++i){
		if( input[i] == '(' )open_parenthesis++;
		if( input[i] == ')' )open_parenthesis--;
	}
	
	return open_parenthesis;//unmatched parenthesis
}


int is_constant(size_t start, size_t end, char *input){
	int i = start;
	int after_token = 0;
	int is_first_non_whitespace = 1;
	while(is_whitespace(input[i]) && i<end)i++;
	
	while(i<end){
		if(is_first_non_whitespace){
			if(!is_numeric(input[i]) && input[i]=='-')return FALSE;
			is_first_non_whitespace = 1;
		}
		
		if(!is_numeric(input[i]) && !is_whitespace(input[i])){
			return 0;
		} else if( is_whitespace(input[i])) {
			i++;
			while(i<end){
				if(!is_whitespace(input[i]))return FALSE;
			}
		} else {
			i++;
		}
	}
	
	return TRUE;
}


int is_name(size_t start, size_t end, char *input){
	int i = start;
	int after_token = 0;
	int is_first_non_whitespace = 1;
	while(is_whitespace(input[i]) && i<end)i++;
	
	while(i<end){
		if(is_first_non_whitespace){
			//won't accept a name begining with a number
			if(is_numeric(input[i]))return FALSE;
			is_first_non_whitespace = 0;
		}
		
		if(!is_alphanumeric(input[i]) && !is_whitespace(input[i])){
			return 0;
		} else if( is_whitespace(input[i])) {
			i++;
			while(i<end){
				if(!is_whitespace(input[i]))return FALSE;
			}
		} else {
			i++;
		}
	}
		
	return TRUE;
}


int is_constant_or_name(size_t start, size_t end, char *input){
	if(is_constant(start,end,input))return TRUE;
	if(is_name(start,end,input))return TRUE;
	return FALSE;
}


size_t get_next_char(size_t start, size_t end, char token, char *input){
	for(int i = start; i < end; ++i){
		if( input[i] == token)return i;
	}
	return -1;
}


int is_function(size_t start, size_t end, char *input){
	size_t pivot = get_next_char(start, end, '(', input);
	if(pivot > 0){
		if(is_name(start,pivot,input) 
			&& is_parenthesized(pivot,end,input))return TRUE;
	}
	return FALSE;
}


int is_simple_math(size_t start, size_t end, char *input){
	size_t pivot1, op;
	for(pivot1=start; pivot1<end && is_constant_or_name(start,pivot1+1,input);++pivot1);
	
	//ended prematurely
	if(pivot1==start || pivot1==end)return FALSE;
	
	for(op=pivot1;op < end && !is_operator(input[op]); ++op);
	
	if(op==end || !is_operator(input[op]))return FALSE;
	
	if(op+1==end || !is_constant_or_name(op+1,end,input))return FALSE;
	
	return TRUE;
}


size_t find_least_precedent(size_t start, size_t end, char *input){
	size_t least_location = -1;
	int least_precedence = 100000000;//just a high number. nothing special
	
	int open_parenthesis = 0;
	
	for(int i=start; i<end; ++i){
		if( input[i]=='(' )open_parenthesis++;
		if( input[i]==')' )open_parenthesis--;
		
		//operate at the same parenthetical level
		if(open_parenthesis == 0){
			int temp = enumerate_precedence(input[i]);
			if(temp != -1 && temp<least_precedence){
				//we've found a valid candidate
				least_precedence = temp;
				least_location = i;
			}
		}
	}
	
	return least_location;
}


//a function to get the end of left token
size_t get_left_token(size_t start, size_t end, char *input){
	size_t result = start;
	size_t temp = find_least_precedent(start,end,input);
	
	if(temp != -1){
		while(!is_alphanumericparenthetic(input[temp]))temp--;
		return ++temp;//shift over to avoid cutting off last char.
	}
	/*
	while( result<end && 
		(is_constant_or_name(start, result+1, input) || 
			is_function(start, result+1, input) ||
			is_parenthesized(start, result+1, input) ||
			unclosed_parenthesis(start, result+1, input) > 0
		)
	)result++;
	
	if(is_parenthesized(start,result+1,input))result+=2;
	
	if(result==start || result==end)return -1;
	return result;
	*/
	return -1;
}


//a function to get the begining of the right token
size_t get_right_token(size_t start, size_t end, char *input){
	size_t result = get_left_token(start, end, input);
	
	while(!is_alphanumericparenthetic(input[result]) && result<end)result++;
	
	if(result==start || result==end)return -1;
	return result;
}


void move_into_parenthesis( size_t *start, size_t *end, char *input){
	if(is_parenthesized(*start,*end,input)){
		while(unclosed_parenthesis(*start,*end,input) ==0 && *start < *end)*start = *start+1;
		while(unclosed_parenthesis(*start,*end,input) !=0 && *start < *end)*end = *end-1;
	}
}


char get_math_operator_from_left(size_t start, size_t end, char *input){
	size_t i = get_left_token(start, end, input);
	
	while(is_whitespace(input[i]))i++;
	
	if(is_operator(input[i]))return input[i];
	
	return 0;
}


char get_math_operator_from_right(size_t start, size_t end, char *input){
	size_t i = get_right_token(start, end, input)-1;
	
	while(is_whitespace(input[i]))i--;
	
	if(is_operator(input[i]))return input[i];
	
	return 0;
}

