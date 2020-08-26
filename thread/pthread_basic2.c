#include"myh.h"


struct Data
{
    int x;
    int y;
};


void* t_func(void* data)
{
    struct Data d = *((struct Data *)data);
    return (void*)(d.x + d.y);
}


int main()
{
    pthread_t thread;
    int ret;
    int status;
    struct Data data;
    data.x=11;
    data.y=3;

    ret=pthread_create(&thread,NULL,t_func,(void*)&data);

    if(ret<0)
    {
        perror("Error : prhread_crete():\n");
        exit(-1);
    }

    pthread_join(thread,(void**)&status);

    print("return value:%d\n",status);

    return 0;

}