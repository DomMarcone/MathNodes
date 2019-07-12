//MathNodes.cpp

#include "MathNodes.hpp"
#include <cmath>

//Begin MathNode
MathNode::MathNode(){}

MathNode::~MathNode(){}
MathNode * MathNode::copy(){ return new MathNode(); }

inline float MathNode::getValue(){return 0.f;}
//End MathNode


//Begin ConstantNode
ConstantNode::ConstantNode(float v){
	value = v;
}

ConstantNode::~ConstantNode(){}
MathNode * ConstantNode::copy(){ return new ConstantNode(value); }


inline float ConstantNode::getValue(){
	return value;
}
//End ConstantNode


//Begin VariableNode
VariableNode::VariableNode(float *v){
	value_ptr = v;
}

VariableNode::~VariableNode(){}
MathNode * VariableNode::copy(){ return new VariableNode(value_ptr); }


inline float VariableNode::getValue(){
	return *value_ptr;
}
//End VariableNode


//Begin FunctionNode
FunctionNode::FunctionNode( float (*fp)() ){
	func_ptr = fp;
}

FunctionNode::~FunctionNode(){}
MathNode * FunctionNode::copy(){ return new FunctionNode(func_ptr); }


inline float FunctionNode::getValue(){
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

MathNode * Function1ParamNode::copy(){ return new Function1ParamNode(func_ptr,param); }

inline float Function1ParamNode::getValue(){
	if(param==0)return 0.f;//handle null parameter
	return func_ptr(param->getValue());
}
//End Function1ParamNode


//Begin DivideNode
DivideNode::DivideNode(MathNode *a, MathNode *b){
	left = a;
	right = b;
}

MathNode * DivideNode::copy(){ return new DivideNode(left->copy(), right->copy()); }

DivideNode::~DivideNode(){
	delete left;
	delete right;
}

inline float DivideNode::getValue(){
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

MathNode *MultiplyNode::copy(){ return new MultiplyNode(left->copy(), right->copy()); }

inline float MultiplyNode::getValue(){
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

MathNode *SubtractNode::copy(){ return new SubtractNode(left->copy(),right->copy()); }

inline float SubtractNode::getValue(){
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

MathNode *AddNode::copy(){ return new AddNode(left->copy(),right->copy()); }

inline float AddNode::getValue(){
	return left->getValue() + right->getValue();
}
//End AddNode


//Begin ModulusNode
ModulusNode::ModulusNode(MathNode *a, MathNode *b){
	left = a;
	right = b;
}

ModulusNode::~ModulusNode(){
	delete left;
	delete right;
}

MathNode *ModulusNode::copy(){ return new ModulusNode(left->copy(), right->copy()); }

inline float ModulusNode::getValue(){
	return fmod(left->getValue(), right->getValue());
}
//End ModulusNode


//Begin ExponentNode
ExponentNode::ExponentNode(MathNode *a, MathNode *b){
	left = a;
	right = b;
}

ExponentNode::~ExponentNode(){
	delete left;
	delete right;
}

MathNode *ExponentNode::copy(){ return new ExponentNode(left->copy(), right->copy()); }

inline float ExponentNode::getValue(){
	return powf(left->getValue(), right->getValue());
}
//End ExponentNode


//Begin ErrorNode
ErrorNode::ErrorNode(){}

ErrorNode::~ErrorNode(){}

MathNode * ErrorNode::copy(){return new ErrorNode();}

inline float ErrorNode::getValue(){
	return 0.f;
}
//End ErrorNode

