#include"myl.h"

void sighandler(int sig)
{
    static int count =0;
    print("child sig num : %d count: %d\n",sig,++count);
    //signal(SIGINT,SIG_DFL);

}

int main()
{
    int count=10;
    signal(SIGINT,sighandler);

    while(count--)
    {
        print("hello~ \n");
        sleep(1);
    }
    return 0;
    
}