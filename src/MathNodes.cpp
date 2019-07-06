//MathNodes.cpp

#include "MathNodes.hpp"


//Begin MathNode
MathNode::MathNode(){}

MathNode::~MathNode(){}
MathNode * MathNode::copy(){return new MathNode();}

float MathNode::getValue(){return 0.f;}
//End MathNode


//Begin ConstantNode
ConstantNode::ConstantNode(float v){
	value = v;
}

ConstantNode::~ConstantNode(){}
MathNode * ConstantNode::copy(){return new ConstantNode(value);}


float ConstantNode::getValue(){
	return value;
}
//End ConstantNode


//Begin VariableNode
VariableNode::VariableNode(float *v){
	value_ptr = v;
}

VariableNode::~VariableNode(){}
MathNode * VariableNode::copy(){return new VariableNode(value_ptr);}


float VariableNode::getValue(){
	return *value_ptr;
}
//End VariableNode


//Begin FunctionNode
FunctionNode::FunctionNode( float (*fp)() ){
	func_ptr = fp;
}

FunctionNode::~FunctionNode(){}
MathNode * FunctionNode::copy(){return new FunctionNode(func_ptr);}


float FunctionNode::getValue(){
	return func_ptr();
}
//End FunctionNode


//Begin Function1ParamNode
Function1ParamNode::Function1ParamNode( float (*fp)(float), MathNode *p){
	func_ptr = fp;
	param = p;
}

Function1ParamNode::Function1ParamNode( float (*fp)(float)){
	func_ptr = fp;
	param = 0;
}

Function1ParamNode::~Function1ParamNode(){
	delete param;
}

void Function1ParamNode::addParam(MathNode *a){
	param = a;
}

MathNode * Function1ParamNode::copy(){return new Function1ParamNode(func_ptr,param);}

float Function1ParamNode::getValue(){
	if(param==0)return 0.f;//handle null parameter
	return func_ptr(param->getValue());
}
//End Function1ParamNode


//Begin DivideNode
DivideNode::DivideNode(MathNode *a, MathNode *b){
	left = a;
	right = b;
}

MathNode * DivideNode::copy(){return new DivideNode(left,right);}

DivideNode::~DivideNode(){
	delete left;
	delete right;
}

float DivideNode::getValue(){
	return left->getValue()/right->getValue();
}
//End DivideNode


//Begin MultiplyNode
MultiplyNode::MultiplyNode(MathNode *a, MathNode *b){
	left = a;
	right = b;
}

MultiplyNode::~MultiplyNode(){
	delete left;
	delete right;
}

MathNode * MultiplyNode::copy(){return new MultiplyNode(left,right);}

float MultiplyNode::getValue(){
	return left->getValue()*right->getValue();
}
//End MultiplyNode


//Begin SubtractNode
SubtractNode::SubtractNode(MathNode *a, MathNode *b){
	left = a;
	right = b;
}

SubtractNode::~SubtractNode(){
	delete left;
	delete right;
}

MathNode * SubtractNode::copy(){return new SubtractNode(left,right);}

float SubtractNode::getValue(){
	return left->getValue() - right->getValue();
}
//End SubtractNode


//Begin AddNode
AddNode::AddNode(MathNode *a, MathNode *b){
	left = a;
	right = b;
}

AddNode::~AddNode(){
	delete left;
	delete right;
}

MathNode * AddNode::copy(){return new AddNode(left,right);}

float AddNode::getValue(){
	return left->getValue() + right->getValue();
}
//End AddNode


//Begin ErrorNode
ErrorNode::ErrorNode(){}

ErrorNode::~ErrorNode(){}

MathNode * ErrorNode::copy(){return new ErrorNode();}

float ErrorNode::getValue(){
	return 0.f;
}
//End ErrorNode

