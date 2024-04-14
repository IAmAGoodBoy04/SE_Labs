/* Create a Chat Bot using Shared Memory in Linux

In this assignment, you will implement a chat bot using shared memory in Linux. The chat bot should communicate with the user using the shared memory segment and respond to the user's messages based on the pre-defined rules.

Here are the steps to follow:
1. Define the message format: Decide on the message format that will be used to communicate between the chat bot and the user. For example, the message format could be a string with a pre-defined prefix for the chat bot's response.
2. Create a shared memory segment: Use System V IPC mechanisms to create a shared memory segment. Use the shmget() function to create the shared memory segment and get a shared memory identifier.
3. Attach to the shared memory segment: Use the shmat() function to attach to the shared memory segment and get a pointer to the shared memory segment.
4. Implement the chat bot logic: Write code that listens for messages from the user and responds appropriately based on pre-defined rules. For example, if the user sends a message starting with "Hi", the chat bot could respond with "Hello, how can I help you today?".
5. Send the chat bot's response: After the chat bot has generated a response, write the response to the shared memory segment.
6. Wait for the user's next message: After writing the response to the shared memory segment, wait for the user to send the next message.
7. Detach from the shared memory segment: Use the shmdt() function to detach from the shared memory segment.
8. Clean up the shared memory segment: When the chat bot is done, use the shmctl() function to delete the shared memory segment. */

#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/sem.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/shm.h>
#include<string.h>

struct sembuf vop,pop;


#define sem_wait(sem_id) semop(sem_id,&pop,1)
#define sem_post(sem_id) semop(sem_id,&vop,1)


void process_response(char* str,char* response){
    if(str[strlen(str)-1]='\n'){
        str[strlen(str)-1]='\0';
    }
    if(strcmp(str,"Hi")==0){
        strcpy(response,"Hello!");
    }
    else if(!strcmp(str,"Are you the chatbot i made for OS exp 8?")){
        strcpy(response,"Yes, I am your submission for OS exp 8");
    }
    else if(!strcmp(str,"How many statements did I program you to answer")){
        strcpy(response,"You programmed me to answer a total 9 differnet questions");
    }
    else if(!strcmp(str,"So i have to type 10 questions, right?")){
        strcpy(response,"Yes, 9 to show that you hardcoded answers to 9 questions, and 1 to show the deault case.");
    }
    else if(!strcmp(str,"Do you think writing these questions and answers must have been boring?")){
        strcpy(response,"Yeah, i think so.");
    }
    else if(!strcmp(str,"Did you know i did this while i was travelling in a train")){
        strcpy(response,"How would I know, am i supposed to?");
    }
    else if(!strcmp(str,"Now i have to remember all these questions too, ::sad_face")){
        strcpy(response,"You should have thought of this, this was a very stupid decision");
    }
    else if(!strcmp(str,"Don't you lecture me, I am the one writing both the questions and answers")){
        strcpy(response,"Please refrain from emotionally charge statements in prompts, i am not a large language model not developed by openAI, i am not designed to answer such questions.");
    }
    else if(!strcmp(str,"Was that 9 questions?")){
        strcpy(response,"Yes. Cosgratulations!! You made it through.");
    }
    else{
        strcpy(response,"Invalid prompt");
    }
}
int main(){
    int shmid=shmget(IPC_PRIVATE,1024*sizeof(char),0777|IPC_CREAT);
    vop.sem_flg=pop.sem_flg=0;
    vop.sem_num=vop.sem_num=0;
    vop.sem_op=1;
    pop.sem_op=-1;
    
    int sem_client=semget(IPC_PRIVATE,1,0777|IPC_CREAT);
    int sem_server=semget(IPC_PRIVATE,1,0777|IPC_CREAT);
    semctl(sem_client,0,SETVAL,0);
    semctl(sem_server,0,SETVAL,0);

    if(fork()==0){
        int iterations=0;
        char* str;
        printf("client process initiated with pid = %d\nyou may start typing a message\n",getpid());
        while(iterations<10){
            sem_wait(sem_client);
            str=(char*)shmat(shmid,0,0);
            printf("User: ");  
            fgets(str,1023,stdin);
            iterations++;
            shmdt(str);
            sem_post(sem_server);
        }
        

    }
    else{
        int iterations=0;
        printf("server process initiated with pid = %d\n",getpid());
        char* str,*response;
        response=malloc(1024*sizeof(char));
        sem_post(sem_client);
        while(iterations<10){
            sem_wait(sem_server);
            str=shmat(shmid,0,0);
            process_response(str,response);
            printf("Chatbot: %s\n",response);
            iterations++;
            shmdt(str);
            sem_post(sem_client);
        }

        free(response);
        shmctl(shmid,IPC_RMID,0);
    }

return 0;
}