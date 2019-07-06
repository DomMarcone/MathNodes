//test_parenthesize.c
#include <stdio.h>
#include <string.h>

#include "parenthesize.h"

#define BUFFER_SIZE 128

char * torf(int i){
	if(i)return "true";
	return "false";
}

void main(){
	char temp[BUFFER_SIZE];
	
	while(1){
		int len;
		printf(">");
		gets(temp);
		len = strlen(temp);
		
		printf("strlen() = %d\n",len);
		printf("is_parenthesized() = %s\n",torf(is_parenthesized(0,len,temp)));
		printf("unclosed_parenthesis() = %d\n",unclosed_parenthesis(0,len,temp));
		printf("is_constant() = %s\n",torf(is_constant(0,len,temp)));
		printf("is_name() = %s\n",torf(is_name(0,len,temp)));
		printf("is_function() = %s\n",torf(is_function(0,len,temp)));
		printf("is_simple_math() = %s\n",torf(is_simple_math(0,len,temp)));
		printf("get_left_token() = %d\n",get_left_token(0,len,temp));
		printf("get_right_token() = %d\n",get_right_token(0,len,temp));
		printf("get_math_operator_from_left() = %c\n",get_math_operator_from_left(0,len,temp));
		printf("get_math_operator_from_right() = %c\n",get_math_operator_from_right(0,len,temp));
		
		{
			size_t l = 0, r = len;
			move_into_parenthesis(&l,&r,temp);
			printf("move_into_parenthesis() = %d, %d\n",l,r);
		}
		
		printf("\n");
	}
	
}
