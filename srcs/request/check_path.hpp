# ifndef CHECK_PATH_HPP
# define CHECK_PATH_HPP

#include "../headers_cpp.hpp"
#include "../server/client.hpp"

class Check_path
{
    private:

        void    check_transfer_encoding(std::list<Client *>::iterator iter);
        void    check_uri(std::list<Client *>::iterator iter);

    public:

        int skip;

        Check_path(std::list<Client *>::iterator iter);
        Check_path();
};
#endif