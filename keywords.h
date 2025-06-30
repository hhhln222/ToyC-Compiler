#pragma once
#include <unordered_set>
#include <string>

const std::unordered_set <std::string> Keywords =
{
	"int","void","if","else","while","break","continue","return"
};

const std::unordered_set <std::string> Operators =
{
	"+","-","*","/","%","==","!=","<=","<",">=",">","=","!","&&","||"
};

const std::unordered_set <std::string> singleCharOperators =
{
	'+','-','*','/','%','!','=','>','<','&','|','(',')','{','}',';',','
};