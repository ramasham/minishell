#include <signal.h>
#include <unistd.h>

void    test_handle(int signum)
{
    return;
}

int main()
{
    signal(SIGINT, test_handle);
    sleep(10000);
}
