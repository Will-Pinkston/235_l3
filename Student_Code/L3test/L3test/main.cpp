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
    cout << calc->postfixToInfix(one) << endl;
    
    return 0;
}
