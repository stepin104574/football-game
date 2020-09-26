#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
// Define message queue structure
struct message 
{
   long msg_type;
   char msg[30];
} ;

void receiver()
{
   int i;
   struct message pass[1];
     key_t my_key;
   int msg_id;
   my_key = ftok("progfile", 65); //create unique key
   msg_id = msgget(my_key, 0666 | IPC_CREAT); //create message queue and return id
 
      msgrcv(msg_id,&pass[0],sizeof(pass[0]), 1, 0); //used to receive message
      printf("Received the ball : %s \n", pass[0].msg);// display the message
    msgctl(msg_id, IPC_RMID, NULL); //destroy the message queue
}
