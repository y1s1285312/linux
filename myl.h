#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<signal.h>
#include<wait.h>
#include<string.h>
#include<errno.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<sys/shm.h>



#define print printf
#define KEY_VALUE (key_t)1234
#define MAX_TEXT 512

struct my_msg_st
{
    long int my_msg_type;
    unsigned long int total;
    char some_text[BUFSIZ];

};
