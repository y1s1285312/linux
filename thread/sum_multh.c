#include"myh.h"

unsigned long end;
unsigned long result[10]={0,};
unsigned long num_thread;

void* t_func(void* data)
{
    int id = (int)data;
    unsigned long s = ((end*(id+1))/num_thread)+1;
    unsigned long e = (end*(id+2))/num_thread;
    unsigned long total=0;
    for(unsigned long i = s ;i<=e;i++)total+=i;
    //print("%d : %ld\n",id,total);
    result[id] = total;
    //print("im %d thread end is %ld\n",(int)data,end);
    return 0;
}



int main(int argc, char* argv[])
{
    pthread_t thread;
    int ret;
    int status;
    
    num_thread = atoi(argv[2]);

    end = (unsigned long)atoi(argv[1]);

    for(int i=0;i<num_thread-1;i++)
    ret=pthread_create(&thread,NULL,t_func,(void*)i);
    
    for(int i=0;i<num_thread-1;i++)pthread_join(thread,NULL);

    if(ret<0)
    {
        perror("Error : prhread_crete():\n");
        exit(-1);
    }

    unsigned long s = 1;
    unsigned long e = end/num_thread;
    unsigned long total=0;

    for(unsigned long i = s ;i<=e;i++)total+=i;
    
    //print("%ld\n",total);

    for(int i=0;i<num_thread-1;i++)total+=result[i];

    print("return value:%ld\n",total);

    return 0;

}