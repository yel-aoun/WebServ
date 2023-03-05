#include "parsing_webserv.hpp"

void	isempty(std::string str)
{
	if (str.empty())
	{
		std::cout << "Error! Empty string";
		exit(1);
	}
}

int main(int argc, char **argv)
{
    std::string	str1;
	if (argc == 2)
	{
		str1 = argv[1];
		isempty(str1);
		std::ifstream filein;
		filein.open(str1);
		if (filein)
		{
			while (filein.good())
			{
				getline(filein, str1);
				str1+='\n';
				// mainstr += str1;
				std::cout << str1;
			}
			filein.close();
		}
		else
			std::cout << "Error! File doesn't exist or it lacks the permission to read from it" << std::endl;
	}
	else
		std::cout << "Error! Either you got too many or not enough arguments" << std::endl;
}