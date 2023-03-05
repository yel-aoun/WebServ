# include "webserv.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "incorrect number of argument's"<<std::endl;
    }
    webserv web(argv[1]);
}