#pragma once
#include<iostream>
#include<fstream>


static std::string ReadFile(std::string filePaht) {
	std::ifstream myReadFile;
	myReadFile.open(filePaht.c_str());

	char output;
	std::string outString;
	if (myReadFile.is_open())
	{
		while (!myReadFile.eof())
		{
			//myReadFile >> output;
			output = myReadFile.get();
			outString.push_back(output);
			//	std::cout << output;

		}
	}
	myReadFile.close();
	outString.pop_back();
	return outString;
}
