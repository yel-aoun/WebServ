# include "webserv.hpp"

webserv::webserv(std::string conf_file)
{
	int i = 0;
    if (conf_file.empty())
    {
        std::cout << "Error! Empty string you must provide a config file";
		exit(1);
    }
	size_t extension = conf_file.rfind(".conf");
	if (extension == -1 || extension + 5 != conf_file.length())
	{
		std::cout << "Error! Please check the extension" << std::endl;
		exit(1);
	}
    std::ifstream filein;
	filein.open(conf_file);
	if (filein)
	{
		while (filein.good())
		{
			getline(filein, conf_file);
			if (conf_file.find("{") != -1)
				i++;
			if (conf_file.find("}") != -1)
				i--;
			if (i < 0)
			{
				std::cout << "Error! Please close every bracket" << std::endl;
				exit (1);
			}
            config.push_back(conf_file);
		}
		filein.close();
	}
	if (i != 0)
	{
		std::cout << "Error! Please close every bracket" << std::endl;
		exit (1);
	}
	location loc(config);
    for(std::list<std::string>::iterator it = config.begin(); it != config.end(); ++it)
    {
        std::cout << *it << std::endl;
    }
}