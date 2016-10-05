
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
    stringstream sOut;
    stringstream sIn;
    stack<char> ops;
    
    sIn << infixExpression;
    char check;
    int numparen = 0;
    int numbracket = 0;
    int numbrace = 0;
    bool inOp = false;
    
    while (sIn >> check)
    {
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
            if (check == '(') numparen++;
            else if (check == '[') numbracket++;
            else if (check == '{') numbrace++;
        }
        else if (sOut.str().empty())
        {
            return "invalid";
        }
        else if (check == '+' || check == '-')//low
        {
//            if (inOp == true)
//            {
//                return "invalid";
//            }
            inOp = true;
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
//            if (inOp == true)
//            {
//                return "invalid";
//            }
            inOp = true;
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
            if (check == ')')
            {
                numparen --;
                if (numbrace == -1)
                {
                    return "invalid";
                }
            }
            else if (check == ']')
            {
                numbracket --;
                if (numbrace == -1)
                {
                    return "invalid";
                }
            }
            else if (check == '}')
            {
                numbrace --;
                if (numbrace == -1)
                {
                    return "invalid";
                }
            }
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
//        if (priorityCheck(ops) == immediate)
//        {
//            if (ops.top() == ')')
//            {
//                if (numparen <= 0)
//                {
//                    return "invalid";
//                }
//            }
//            else if (ops.top() == ']')
//            {
//                if (numbracket <= 0)
//                {
//                    return "invalid";
//                }
//            }
//            else if (ops.top() == '}')
//            {
//                if (numbrace <= 0)
//                {
//                    return "invalid";
//                }
//            }
//        }
        else
        {
            char hold = ops.top();
            sOut << hold << " ";
            ops.pop();
        }
    }
    //checking for value parity
    if (postfixEvaluate(sOut.str()) == "invalid")
    {
        return "invalid";
    }
    //
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






