//MathTreeBuilder.hpp
#include "MathNodes.hpp"
#include "parenthesize.h"

#include <vector>
#include <string>

/*************************************************
** Define MATH_TREE_VERBOSITY to get messages 	**
** from the parser.								**
*************************************************/
//#define MATH_TREE_VERBOSITY

typedef struct {
	const char *name;
	float *value_ptr;
}variable;


typedef struct {
	const char *name;
	float (*func_ptr)();
}function;


typedef struct {
	const char *name;
	float (*func_ptr)(float);
}function1param;


class MathTreeBuilder{
private:
	std::vector<variable> variables;
	std::vector<function> functions;
	std::vector<function1param> function1params;
public:
	MathNode *parse(char *input);
	
	MathNode *parseSub(size_t start, size_t end, char *input);
	
	void addVariable(float *ptr, const char *name);
	void addVariable(float *ptr, const std::string &name);
	
	void addFunction(float (*fp)(), const char *name);
	void addFunction(float (*fp)(), const std::string &name);
	
	//overloads
	void addFunction(float (*fp)(float), const char *name);
	void addFunction(float (*fp)(float), const std::string &name);
	
	void addFunction1Param(float (*fp)(float), const char *name);
	void addFunction1Param(float (*fp)(float), const std::string &name);
	
	MathNode *getVariable(char *name);
	MathNode *getFunction(char *name);
	Function1ParamNode *getFunction1Param(char *name);
};
