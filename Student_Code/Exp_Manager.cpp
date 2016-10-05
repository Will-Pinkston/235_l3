
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


int priorityCheck (stack<char>ops)
{
    if (ops.size() == 0)
    {
        return empty;
    }
    else
    {
        char check = ops.top();
        if (check == '(' || check == '[' || check == '{')
        {
            return wild;
        }
        else if (check == '+' || check == '-')
        {
            return low;
        }
        else if (check == '*' || check == '/' || check == '%')
        {
            return high;
        }
        else if (check == ')' || check == ']' || check == '}')
        {
            return immediate;
        }
        else
        {
            return -1;
        }
    }
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
      }
      else if (c == '}')
      {
          if (checker.top() == '{')
          {
              checker.pop();
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
    stringstream ss1;
    stringstream ss2;
    
    ss1 << postfixExpression;
    string c;
    char check;
    stack<string> calc;
    
    while (ss1 >> check)
    {
        if (check == '+' || check == '-' || check == '*' || check == '/' || check == '%')
        {
            if (calc.size() <= 1)
            {
                return "invalid";
            }
            else
            {
                string second = calc.top();
                calc.pop();
                string first = calc.top();
                calc.pop();
                string result;
                calc.push(result = "( " + first + " " + check + " " + second + " )");
            }
        }
        else if (isdigit(check))
        {
            ss1.seekg(-1, ios_base::cur);
            float icheck;
            if (ss1 >> icheck)
            {
                int adjust = 0;
                stringstream ss3;
                ss3 << icheck;
                char ch;
                while (ss3 >> ch)
                {
                    if (ch == '.') return "invalid";
                    adjust++;
                }
                adjust *= -1;
                ss1.seekg(adjust, ios_base::cur);
                ss1 >> c;
                calc.push(c);
            }
            else
            {
                return "invalid";
            }
        }
        else
        {
            return "invalid";
        }
    }
    ss2 << calc.top();
    calc.pop();
    if (calc.size() == 0)
    {
        return ss2.str();
    }
    else
    {
        return "invalid";
    }
}
//------------------------------------------------------------------------


//------------------------------------------------------------------------
string Exp_Manager::infixToPostfix(string infixExpression)
{
    /*
     * Converts an infix expression into a postfix expression
     * and returns the postfix expression
     *
     * - The given infix expression will have a space between every number or operator.
     * - The returned postfix expression must have a space between every number or operator.
     * - Check lab requirements for what will be considered invalid.
     *
     * return the string "invalid" if infixExpression is not a valid infix expression.
     * otherwise, return the correct postfix expression as a string.
     */
    
    /*
     precedence:
     3 immediate ) } ]
     2 high * / %
     1 Low + -
     0 wild ( { [
    
     only place an operator if the top element has lower precedence
     if equal or greater, pop until you can place
     if a closing parenthesis, pop until you reach the opening parenthesis
     once at end of string, pop all operators
     always put numbers into the output string immediatly
     */
    stringstream sOut;
    stringstream sIn;
    stack<char> ops;
    
    sIn << infixExpression;
    char check;
//    int priorityTop = empty;
    while (sIn >> check)
    {
//        std::cout << sOut.str() << endl;
        if (isdigit(check))
        {
            //pull the full number into the sOut sstream
            sIn.seekg(-1, ios_base::cur);
            float icheck;
            if (sIn >> icheck)
            {
                stringstream checkint;
                checkint << icheck;
                char ch;
                while (checkint >> ch)
                {
                    if (ch == '.') return "invalid";
                }
                sOut << icheck << " ";
            }
            else
            {
                return "invalid";
            }
        }
        else if (check == '(' || check == '[' || check == '{' )//wild
        {
            ops.push(check);
        }
        else if (check == '+' || check == '-')//low
        {
            if (priorityCheck(ops)  == wild || priorityCheck(ops) == empty)
            {
                ops.push(check);
            }
            else
            {
                while (priorityCheck(ops) != empty && priorityCheck(ops) != wild)
                {
                    char hold = ops.top();
                    sOut << hold << " ";
                    ops.pop();
                }
                ops.push(check);
            }
        }
        else if (check == '*' || check == '/' || check == '%')//high
        {
            if (priorityCheck(ops) == empty || priorityCheck(ops) <= low)
            {
                ops.push(check);
            }
            else
            {
                while (priorityCheck(ops) == high)
                {
                    char hold = ops.top();
                    sOut << hold << " ";
                    ops.pop();
                }
                ops.push(check);
            }
        }
        else if (check == ')' || check == ']' || check == '}')//immediate
        {
            while (priorityCheck(ops) != empty && priorityCheck(ops) != wild)
            {
                char hold = ops.top();
                sOut << hold << " ";
                ops.pop();
            }
            ops.pop();
        }
        else //there's something wrong in the stream
        {
            return "invalid";
        }
    }
    while (priorityCheck(ops) != empty)
    {
        if (priorityCheck(ops) == wild)
        {
            return "invalid";
        }
        else
        {
            char hold = ops.top();
            sOut << hold << " ";
            ops.pop();
        }
    }
    return sOut.str();
}
//------------------------------------------------------------------------


//------------------------------------------------------------------------
string Exp_Manager::postfixEvaluate(string postfixExpression)
{
    stringstream ss;
    ss << postfixExpression;
    int c;
    char check;
    stack<int> calc;
    while (ss >> check)
    {
        if (check == '+' || check == '-' || check == '*' || check == '/' || check == '%')
        {
            if (calc.size() <= 1)
            {
                return "invalid";
            }
            else
            {
                int second = calc.top();
                calc.pop();
                int first = calc.top();
                calc.pop();
                int result;
                if (check == '+')
                {
                    calc.push(result = first + second);
                }
                else if (check == '-')
                {
                    calc.push(result = first - second);
                }
                else if (check == '*')
                {
                    calc.push(result = first * second);
                }
                else if (check == '/')
                {
                    if (second == 0)
                    {
                        return "invalid";
                    }
                    else
                    {
                        calc.push(result = first / second);
                    }
                }
                else if (check == '%')
                {
                    calc.push(result = first % second);
                }
            }
        }
        else if (isdigit(check))
        {
            ss.seekg(-1, ios_base::cur);
            ss >> c;
            calc.push(c);
        }
        else
        {
            return "invalid";
        }
    }
    stringstream ss2;
    ss2 << calc.top();
    return ss2.str();
}
//------------------------------------------------------------------------






