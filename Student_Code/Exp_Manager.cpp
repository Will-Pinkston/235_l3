
#include "Exp_Manager.h"
#include <iostream>
//------------------------------------------------------------------------
void printStack (stack<char> writeIt)
{
  if (writeIt.size() == 0)
  {
    std::cout << "stack empty";
  }
  else
  {
    while (writeIt.size() > 0)
    {
      std::cout << writeIt.top();
      writeIt.pop();
    }
  }
  std::cout << endl;
  return;
}
//------------------------------------------------------------------------


//------------------------------------------------------------------------
bool Exp_Manager::isBalanced(string expression)
{
  stringstream ss;
  stack<char> checker;
  ss << expression;
  char c;
  while (ss >> c)
  {
      if ((checker.size() == 0) && (c == '}' || c == ']' || c == ')'))
      {
          return false;
      }
      else if (c == '{' || c == '[' || c == '(')
      {
          checker.push(c);
          std::cout << "pushed" << c << endl;
          printStack(checker);
      }
      else if (c == '}')
      {
          if (checker.top() == '{')
          {
              checker.pop();
              std::cout << "popped" << c << endl;
              printStack(checker);
          }
          else
          {
              return false;
          }
      }
      else if (c == ']')
      {
          if (checker.top() == '[')
          {
              checker.pop();
              std::cout << "popped" << c << endl;
              printStack(checker);
          }
          else
          {
              return false;
          }
      }
      else if (c == ')')
      {
          if (checker.top() == '(')
          {
              checker.pop();
              std::cout << "popped" << c << endl;
              printStack(checker);
          }
          else
          {
              return false;
          }
      }
      else return false;
  }
    if (checker.size() == 0)
    {
        return true;
    }
    else return true;
}
//------------------------------------------------------------------------


//------------------------------------------------------------------------
string Exp_Manager::postfixToInfix(string postfixExpression)
{
  return "";
}
//------------------------------------------------------------------------


//------------------------------------------------------------------------
string Exp_Manager::infixToPostfix(string infixExpression)
{
  return "";
}
//------------------------------------------------------------------------


//------------------------------------------------------------------------
string Exp_Manager::postfixEvaluate(string postfixExpression)
{
  return "";
}
//------------------------------------------------------------------------
