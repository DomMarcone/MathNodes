//parenthesize.h
#pragma once
#ifndef _PARENTHESIZE_H
#define _PARENTHESIZE_H

/*
	separate a string by expressions
	errors evaluate to the constant 0
*/

#ifdef __cplusplus
extern "C" {
#endif

#include <string.h>
#include <stdlib.h>

#ifndef TRUE
	#define TRUE 1
#endif

#ifndef FALSE 
	#define FALSE 0
#endif

int is_whitespace(char c);
int is_operator(char c);
int is_numeric(char c);
int is_alphanumeric(char c);
int is_alphanumericparenthetic(char c);

int is_parenthesized( size_t start, size_t end, char *input);
int unclosed_parenthesis( size_t start, size_t end, char *input);

void move_into_parenthesis( size_t *start, size_t *end, char *input);
size_t get_next_char(size_t start, size_t end, char token, char * input);

int is_constant(size_t start, size_t end, char *input);
int is_name(size_t start, size_t end, char *input);
int is_constant_or_name(size_t start, size_t end, char *input);
int is_function(size_t start, size_t end, char *input);

int enumerate_precedence(char op);
//return the location of an operator of lower precedence (like in PEDMAS)
size_t find_least_precedent(size_t start, size_t end, char *input);

size_t get_left_token(size_t start, size_t end, char *input);
size_t get_right_token(size_t start, size_t end, char * input);

int is_simple_math(size_t start, size_t end, char *input);
char get_math_operator_from_left(size_t start, size_t end, char *input);
char get_math_operator_from_right(size_t start, size_t end, char *input);

#ifdef __cplusplus
}
#endif

#endif