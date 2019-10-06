//MathNodes.hpp
#pragma once
#ifndef _MATH_NODES_HPP
#define _MATH_NODES_HPP

#include "parenthesize.h"


class MathNode{
public:
	MathNode();
	~MathNode();
	virtual MathNode * copy();
	virtual inline float getValue();
};


class ConstantNode : public MathNode{
private:
	float value;
public:
	ConstantNode(float v);
	~ConstantNode();
	MathNode *copy();
	inline float getValue();
};


class VariableNode : public MathNode{
private:
	float *value_ptr;
public:
	VariableNode(float *v);
	~VariableNode();
	MathNode *copy();
	inline float getValue();
};


class FunctionNode : public MathNode{
private:
	float (*func_ptr)();
public:
	FunctionNode(float (*fp)());
	~FunctionNode();
	MathNode *copy();
	inline float getValue();
};


class Function1ParamNode : public MathNode{
private:
	float (*func_ptr)(float);
	MathNode *param;
public:
	Function1ParamNode(float (*func)(float), MathNode *a);
	Function1ParamNode(float (*func)(float));
	~Function1ParamNode();
	void addParam(MathNode *a);
	MathNode *copy();
	inline float getValue();
};


class NotNode : public MathNode{
private:
	MathNode *child;
public:
	NotNode(MathNode *c);
	~NotNode();
	MathNode *copy();
	inline float getValue();
};


class AndNode : public MathNode{
private:
	MathNode *left, *right;
public:
	AndNode(MathNode *a, MathNode *b);
	~AndNode();
	MathNode *copy();
	inline float getValue();
};


class OrNode : public MathNode{
private:
	MathNode *left, *right;
public:
	OrNode(MathNode *a, MathNode *b);
	~OrNode();
	MathNode *copy();
	inline float getValue();
};


class EqualToNode : public MathNode{
private:
	MathNode *left, *right;
public:
	EqualToNode(MathNode *a, MathNode *b);
	~EqualToNode();
	MathNode *copy();
	inline float getValue();
};


class LessThanNode : public MathNode{
private:
	MathNode *left, *right;
public:
	LessThanNode(MathNode *a, MathNode *b);
	~LessThanNode();
	MathNode *copy();
	inline float getValue();
};


class GreaterThanNode : public MathNode{
private:
	MathNode *left, *right;
public:
	GreaterThanNode(MathNode *a, MathNode *b);
	~GreaterThanNode();
	MathNode *copy();
	inline float getValue();
};


class ExponentNode : public MathNode{
private:
	MathNode *left, *right;
public:
	ExponentNode(MathNode *a, MathNode *b);
	~ExponentNode();
	MathNode *copy();
	inline float getValue();
};


class DivideNode : public MathNode{
	MathNode *left, *right;
public:
	DivideNode(MathNode *a, MathNode *b);
	~DivideNode();
	MathNode *copy();
	inline float getValue();
};


class MultiplyNode : public MathNode{
private:
	MathNode *left, *right;
public:
	MultiplyNode(MathNode *a, MathNode *b);
	~MultiplyNode();
	MathNode *copy();
	inline float getValue();
};


class SubtractNode : public MathNode{
private:
	MathNode *left, *right;
public:
	SubtractNode(MathNode *a, MathNode *b);
	~SubtractNode();
	MathNode *copy();
	inline float getValue();
};


class AddNode : public MathNode{
private:
	MathNode *left, *right;
public:
	AddNode(MathNode *a, MathNode *b);
	~AddNode();
	MathNode *copy();
	inline float getValue();
};


class ModulusNode : public MathNode{
private:
	MathNode *left, *right;
public:
	ModulusNode(MathNode *a, MathNode *b);
	~ModulusNode();
	MathNode *copy();
	inline float getValue();
};


class ErrorNode : public MathNode{
public:
	ErrorNode();
	~ErrorNode();
	MathNode *copy();
	inline float getValue();
};

#endif //MathNodes.hpp
