#include "server.hpp"

int main(void)
{
    Server s(8080);
    s.run_serve();
}