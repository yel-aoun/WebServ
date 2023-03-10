# include "webserv.hpp"

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
            config.push_back(conf_file);
			if (conf_file.find("server") != std::string::npos)
				count_serv++;
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