#include"myl.h"
#include<time.h>


int main(int argc , char * argv[])
{
    int pid=1;
    int count=1;
    int msgid;
    int process;
    unsigned long int num;
    unsigned long int result =0;
    struct my_msg_st some_data;
    long int msg_to_receive=0;

    clock_t start,end;
    start=clock();

     //1. msgget()
    msgid = msgget(KEY_VALUE,0666 | IPC_CREAT);
    
    //msg queue create fail
    if(msgid < 0) 
    {
        fprintf(stderr,"msgget failed with error: %d\n ",errno); //errno is defined errno.h 
        exit(EXIT_FAILURE);
    }

    if(argc != 3)
    {
        print("Usage : test1 [target] [core]\n");
        exit(0);
    }
    if(!(num=atoi(argv[1])) || !(process = atoi(argv[2])))
    {
        print("Usage : test1 [target] [core]\n");
        exit(0);
    }

    //print("pid : %d\n",getpid());

    while(1)
    {
        clock_t start,end;
        pid=0;
        if(count>process)
            break;

        start=clock();
        pid=fork();
        if(!pid)
        {
            //unsigned long int total=0;
            unsigned long int s=(((num*(count-1))/process)+1);
            unsigned long int e=((num*count)/process);
           
            for(unsigned long int i=s ;i<=e;i++) some_data.total+=i;
            
            //send data
            some_data.my_msg_type=1;
            if( (msgsnd(msgid, (void*)&some_data,MAX_TEXT,0) ) <0 )
            {
                fprintf(stderr,"msgsnd failed with error: %d\n ",errno); //errno is defined errno.h 
                exit(EXIT_FAILURE);
            }
            //print("time : %f sec process : %d ppid : %d\n",((double)(end-start)/CLOCKS_PER_SEC),count,getppid());
            exit(EXIT_SUCCESS);
            end=clock();
        }
        count++;
  
    }
  
    wait(NULL);
    
    count=0;
    while(count<process)
    {
         if( (msgrcv(msgid, (void*)&some_data,BUFSIZ,msg_to_receive,0) ) <0 )
        {
            fprintf(stderr,"msgrcv failed with error: %d\n ",errno); //errno is defined errno.h 
            exit(EXIT_FAILURE);
        }
        result += some_data.total;
        count++;
    }
    print("result : %ld\n",result);

    if(msgctl(msgid,IPC_RMID,0) < 0)
    {
        fprintf(stderr,"msgctl failed with error: %d\n ",errno); //errno is defined errno.h 
        exit(EXIT_FAILURE);
    }
    end=clock();
    //print("time : %f sec\n",((double)(end-start))/CLOCKS_PER_SEC);
    return 0;
}