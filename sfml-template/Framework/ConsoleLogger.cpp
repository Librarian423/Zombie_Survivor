#include "ConsoleLogger.h"
#include <iostream>

void ConsoleLogger::PrintVectorState(Vector2f vec, string name)
{
	cout << name << 
		"(" << vec.x << " " << vec.y << ")" << endl;
}
