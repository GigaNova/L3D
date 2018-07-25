#include "LOBJLoader.h"
#include <string>
#include <istream>
#include <fstream>
#include <sstream>
#include <iterator>

mesh LOBJLoader::loadOBJ(std::string _name)
{
	mesh newMesh;
	std::vector<vector3> tris;

	std::string currentLine;
	std::ifstream infile;
	infile.open("../models/" + _name + ".obj");
	while (!infile.eof())
	{
		getline(infile, currentLine);
		if(currentLine.c_str()[0] == 'v')
		{
			std::istringstream iss(currentLine);
			std::vector<std::string> vertices((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());

			
			tris.push_back({(float)atof(vertices.at(1).c_str()), (float)atof(vertices.at(2).c_str()), (float)atof(vertices.at(3).c_str())});
		}
		else if(currentLine.c_str()[0] == 'f')
		{
			std::istringstream iss(currentLine);
			std::vector<std::string> polygon((std::istream_iterator<std::string>(iss)), std::istream_iterator<std::string>());
			
			newMesh.tris.push_back({
				tris.at(atoi(polygon.at(1).c_str()) - 1),
				tris.at(atoi(polygon.at(2).c_str()) - 1),
				tris.at(atoi(polygon.at(3).c_str()) - 1),
			});
		}
	}

	return newMesh;
}

std::vector<std::string> LOBJLoader::splitString(std::string _string, char _delimiter)
{
	std::stringstream ss(_string);
	std::string item;
	std::vector<std::string> splittedStrings;
	while (getline(ss, item, _delimiter))
	{
		splittedStrings.push_back(item);
	}
	return splittedStrings;
}
