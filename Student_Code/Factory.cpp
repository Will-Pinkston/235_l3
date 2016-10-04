#include "Factory.h"
#include "Exp_Manager.h"
using namespace std;

/*
	Unlike all other documents provided, you may modify this document slightly (but do not change its name)
*/
//=======================================================================================
/*
	createManager()

	Creates and returns an object whose class extends ExpressionManagerInterface.
	This should be an object of a class you have created.

	Example: If you made a class called "ExpressionManager", you might say, "return new ExpressionManager();".
*/
ExpressionManagerInterface* Factory::createManager()
{
	return new Exp_Manager();//Modify this line
}
//=======================================================================================
