#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h> 


int next_string(char string[], int current_case);
int hasher(char final_hash[]);


int main(int argc, char *argv[])
{
    int sockfd = 0, n = 0;
    char recvBuff[1024] = {0};
    char string[64] = {0};
    char initial_hash[512] = {0};
    char final_hash[512] = {0};
    int per_time = 0;
    struct sockaddr_in serv_addr = {0}; 

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(5000); 
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    /***************************************/
    /*            Initiate data             */
    /***************************************/

    n = read(sockfd, recvBuff, sizeof(recvBuff)-1);
    recvBuff[n] = 0;
    per_time = atoi(recvBuff);
    printf("per_time : %d\n",per_time);

    n = read(sockfd, recvBuff, sizeof(recvBuff)-1);
    recvBuff[n] = 0;
    strcpy(initial_hash, recvBuff);    
    printf("initial_hash : %s\n", initial_hash);
    /* Main loop */

    while(1)
    {
        int found = 0;
        n = read(sockfd, recvBuff, sizeof(recvBuff)-1);
        recvBuff[n] = 0;
        strcpy(string, recvBuff);

        printf("starting string : %s\n\n\n\n",string);

        int i;
        for(i=0; i<per_time; i++)
        {

            
            strcpy(final_hash, string);
            hasher(final_hash);
            printf("string %s final_hash %s\n", string, final_hash);
            if(strcmp(initial_hash, final_hash) == 0)
            {
                printf("Gg\n");
                found = 1;
                break;
            }

            next_string(string, strlen(string)-1);        
        }

        if(found != 0)
            break;
    }









    return (0);
}



int next_string(char string[], int current_case) // recursive
{
    if((int)string[current_case] >= 122)
    {
        string[current_case] = string[current_case] - 26;
        next_string(string, current_case-1);
    }
    string[current_case] = ++string[current_case];
    return(0);
}

int hasher(char final_hash[])
{
    //CESEAR ENCRYPTION

    int i = 0;
    for(i=0; i<strlen(final_hash); i++)
    {
        final_hash[i]++;
    }
}

















