#ifndef DELETE_HPP
#define DELETE_HPP
class Client;
class Server;
class Delete
{
    public:
        Delete();
        ~Delete();
        void delete_directory(Client *ctl, Server &serv);
        void Treat_directory(Client *ctl, Server &serv);
        void Treat_File(Client *ctl, Server &serv);
        void erase(Client *ctl, Server &serv);
};
#endif