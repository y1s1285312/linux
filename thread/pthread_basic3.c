#include"myh.h"

void* t_func(void* data)
{
    int * arg =(int*)data;
    *(arg+2) = *arg + *(arg+1);
    return 0;
}


int main()
{
    pthread_t thread;
    int ret;
    int status;
    
    int * arg = (int*)malloc(sizeof(int)*3);
    *arg = 10;
    *(arg+1)=4;
    
    ret=pthread_create(&thread,NULL,t_func,(void*)arg);

    if(ret<0)
    {
        perror("Error : prhread_crete():\n");
        exit(-1);
    }

    pthread_join(thread,NULL);

    print("return value:%d\n",*(arg+2));

    return 0;

}