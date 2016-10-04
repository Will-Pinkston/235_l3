#pragma once
#include "ExpressionManagerInterface.h"
#include <sstream>
#include <string>

class Exp_Manager : public ExpressionManagerInterface
{
private:
  //
public:
  Exp_Manager(){};
  bool isBalanced(string expression);
  string postfixToInfix(string postfixExpression);
  string infixToPostfix(string infixExpression);
  string postfixEvaluate(string postfixExpression);
};
