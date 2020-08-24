#include"myl.h"


int main()
{
    pid_t pid;
    int status;
    int count=5;
    pid = fork();
    
    if(!pid)
    {
        execl("./hello","hello",NULL);
    }

    else
    { 
        sleep(1);
        while(count--)
        {
            kill(pid,SIGINT);
             sleep(2);
        }
    }

    kill(pid,SIGKILL);
    
    return 0;   
}