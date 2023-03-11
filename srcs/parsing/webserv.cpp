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

 void Webserv::parce_config_file(std::string &conf_file)
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
	{
		parce_server	serv(config, i);
	 	this->servers_data.push_back(serv);
	 	i++;
	}
 }

Webserv::Webserv(std::string conf_file)
{
	parce_config_file(conf_file);
	run_webservs();
	// std::list<server>::iterator it = this->servers.begin();
	// while (it != this->servers.end())
	// {
	// 	std::cout << "port is " << (*it).port << std::endl;
	// 	it++;
	// }
}

void Webserv::init_servers()
{
	std::list<parce_server>::iterator iter;

	for(iter = servers_data.begin(); iter != servers_data.end(); iter++)
	{
		Server *sv = new Server(*iter);

		this->servers.push_back(sv);
	}
}

void Webserv::run_webservs()
{
	this->init_servers();
	while (1)
	{
		std::list<Server *>::iterator iter;
		for(iter = this->servers.begin(); iter != this->servers.end(); iter++)
			(*iter)->run_serve();
	}
}