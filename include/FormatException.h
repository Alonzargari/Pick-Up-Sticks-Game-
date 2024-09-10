#pragma once
#include <iostream>
#include <exception>
#include <string>

class FormatException :public std::runtime_error 
{
public:
	FormatException(std::string str);
};