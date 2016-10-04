//
//  main.cpp
//  L3test
//
//  Created by William Pinkston on 10/3/16.
//  Copyright © 2016 Xunil_programming. All rights reserved.
//

#include <iostream>
#include <string>
#include "Factory.h"
#include "Exp_Manager.h"
#include "ExpressionManagerInterface.h"

int main(int argc, const char * argv[]) {
    ExpressionManagerInterface* calc = Factory::createManager();
    string one;
    getline(cin, one);
    if (calc->isBalanced(one))
    {
        cout << "string is balanced." << endl;
    }
    else
    {
        cout << "string is unbalanced." << endl;
    }
    
    return 0;
}
