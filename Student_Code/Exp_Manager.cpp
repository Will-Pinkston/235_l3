
#include "Exp_Manager.h"
#include <iostream>
//------------------------------------------------------------------------
// utility functions
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
      }
      else if (c == '}')
      {
          if (checker.top() == '{')
          {
              checker.pop();
              std::cout << "popped" << c << endl;
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
    else return false;
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
    /*
     * Evaluates a postfix expression returns the result as a string
     *
     * - The given postfix expression will have a space between every number or operator.
     * - Check lab requirements for what will be considered invalid.
     *
     * return the string "invalid" if postfixExpression is not a valid postfix Expression
     * otherwise, return the correct evaluation as a string
     */
    
    stringstream ss;
    ss << postfixExpression;
    char c;
    stack<char> calc;
    while (ss >> c)
    {
        if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            //should these be ints or chars?
            int second = calc.top();
            calc.pop();
            int first = calc.top();
            calc.pop();
            char result;
            if (c == '+')
            {
                calc.push(result = first + second);
            }
            else if (c == '-')
            {
                calc.push(result = first - second);
            }
            else if (c == '*')
            {
                calc.push(result = first * second);
            }
            else if (c == '/')
            {
                calc.push(result = first / second);
            }
        }
        else
        {
            if (isdigit(c))
            {
                calc.push(c);
            }
        }
    }
    stringstream ss2;
    ss2 << calc.top();
    return ss2.str();
}
//------------------------------------------------------------------------






