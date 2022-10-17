#pragma once
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

class ConsoleLogger
{
public:
	static void PrintVectorState(Vector2f vec, string name = "");
};
#define LOG (ConsoleLogger)