#pragma once
#include "LMath.h"

class LOBJLoader
{
public:
	static mesh loadOBJ(std::string _name);
	static std::vector<std::string> splitString(std::string _string, char _delimiter);
};

