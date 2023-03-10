#include "server.hpp"

int main(void)
{
    Server s(8083);
    s.run_serve();
}