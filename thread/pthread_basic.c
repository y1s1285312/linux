#include"myh.h"

int global_var = 6;

void* t_func(void* data)
{
    int id;
    int i=0;
    pthread_t t_id;
    id=*((int*)data);
    global_var ++;
    t_id=pthread_self();
    print("pid : %d, t_id=%lu, id=%d, global_var : %d \n",getpid(),t_id,id,global_var);
    sleep(2);
    return (void*)(id*id);
}

int main()
{
    //posix thread id value
    pthread_t thread[2];
    int ret;
    int status;
    int a=1;
    int b=2;

    print("Init glob_var=%d\n",global_var);
    print("pid=%d\n",getpid());

    //create posix thread
    ret=pthread_create(&thread[0],NULL,t_func,(void*)&a);
    if(ret<0)
    {
        perror("Error : pthread_create():");
        exit(-1);
    }

    ret=pthread_create(&thread[1],NULL,t_func,(void*)&b);
    if(ret<0)
    {
        perror("Error : pthread_create():");
        exit(-1);
    }
    
    pthread_join(thread[0],(void**)&status);
    print("thread_join:%d\n",status);

    pthread_join(thread[1],(void**)&status);
    print("thread_join:%d\n",status);

    print("main thread : global_var=%d\n",global_var);
    return 0;   
}