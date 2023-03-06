# include "webserv.hpp"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "incorrect number of argument's"<<std::endl;
        exit(1);
    }
    webserv web(argv[1]);
}