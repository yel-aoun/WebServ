# include "webserv.hpp"

std::string trim_spaces(std::string& str) {
    std::string::size_type first = str.find_first_not_of(' ');
    if (first == std::string::npos) {
        return "";
    }
    std::string::size_type last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}

std::string	ft_trim_and_replace(std::string conf_file)
{
	int len = conf_file.length();
	int i = 0;
	while (i  < len)
	{
		if (conf_file[i] == '\t')
			conf_file.replace(i, 1, " ");
		i++;
	}
	return (trim_spaces(conf_file));
}

webserv::webserv(std::string conf_file)
{
	int count_location = 0;
	int count_serv = 0;
	int count_loc = 0;
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
			if (conf_file.find("server") != std::string::npos)
				count_serv++;
            config.push_back(ft_trim_and_replace(conf_file));
		}
		filein.close();
	}
	if (i != 0)
	{
		std::cout << "Error! Please close every bracket" << std::endl;
		exit (1);
	}
	i = 0;
	int j = 0;
	while (i < count_serv)
	{ // creat new object for server fill and push back to the servers list
		server	serv(config, i);
	// for (std::list<location>::iterator it = serv.locations.begin();  it != serv.locations.end(); it++)
	// {
	// 	std::cout << "======> " << (*it).root << std::endl; 
	// }
	 	this->servers.push_back(serv);
	 	i++;
	}
	std::list<server>::iterator it = this->servers.begin();
	while (it != this->servers.end())
	{
		std::cout << "port is " << (*it).port << std::endl;
		it++;
	}
    // for(std::list<std::string>::iterator it = config.begin(); it != config.end(); ++it)
    // {
    //     std::cout << *it << std::endl;
    // }
}