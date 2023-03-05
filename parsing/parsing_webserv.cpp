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
		size_t extension = str1.rfind(".conf");
		if (extension == -1 || extension + 5 != str1.length())
		{
			std::cout << "Error! Please check the extension" << std::endl;
			exit(1);
		}
		isempty(str1);
		std::ifstream filein;
		filein.open(str1);
		if (filein)
		{
			while (filein.good())
			{
					getline(filein, str1);
					size_t semi_column = str1.rfind(";");
					if ((semi_column == -1 || str1.length() - 1 != semi_column) && (str1.rfind("{") == -1 && str1.rfind("}") == -1) && (str1 != "location" && str1 != "server"))
					{
						std::cout << "Error! please check that every line has a semi-column" << std::endl;
						exit (1);
					}
				//str1+='\n';
				std::cout << str1 << std::endl;
				// mainstr += str1;

			}
			filein.close();
		}
		else
			std::cout << "Error! File doesn't exist or it lacks the permission to read from it" << std::endl;
	}
	else
		std::cout << "Error! Either you got too many or not enough arguments" << std::endl;
}