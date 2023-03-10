#include "server.hpp"

int main(void)
{
    Server s(8081);
    s.run_serve();
}