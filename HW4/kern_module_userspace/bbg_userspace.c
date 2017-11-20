#include<errno.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include<stdbool.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>


/*enum for different LED states*/
typedef enum led_states
{
  ON = 1,
  OFF = 2
}state;

/*struct for sending packet*/
typedef struct packet_info
{
  uint8_t led_state;
  uint8_t period;
  uint8_t dutycycle;
}packet;


int main(int argc, char *argv[])
{
  int sockfd, newsockfd, port_number, client_length;

  struct sockaddr_in server_address, client_address;

  int n = 0;

  /*check if portnumber is provided*/
  if(argc < 2)
  {
    printf("\nERROR:PORT NUMBER NOT PROVIDED\n");
    exit(1);
  }

  /*create a tcp socket*/
  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if(sockfd < 0)
  { 
    printf("ERROR:SOCKET OPENING");
    exit(1);
  }

  bzero((char *)&server_address, sizeof(server_address));
  port_number = atoi(argv[1]);

  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = INADDR_ANY;
  server_address.sin_port = htons(port_number);

  if(bind(sockfd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0)
  {
    printf("ERROR: BINDING");
  }

  listen(sockfd,5);
  client_length = sizeof(client_address);
  
  /*connection created*/
  newsockfd = accept(sockfd, (struct sockaddr *)&client_address, &client_length);
  if(newsockfd < 0)
  {
    printf("\nERROR: accept\n");
  }

  char recd_part1[10] = {};

  /*opening the character device*/ 
  int fd = 0;
  fd = open("/dev/vigi_char_device", O_RDWR);
  if(fd < 0)
  {
     perror("ERROR: FAILED TO OPEN CHAR DEVICe");
    return errno;
  }
  
  while(1)
  {

    int ret_value = 0;
    printf("\nBBB USERSPACE CODE STARTED\n");

    /*receving from client: to check if command or query*/
    read(newsockfd,recd_part1,sizeof(recd_part1));
    if(strncmp(recd_part1,"command",strlen("command")) == 0)
    {
      packet receive;
      read(newsockfd,&receive,sizeof(receive));
      
      /*write the command request to kernel space*/
      ret_value = write(fd,&receive,sizeof(receive));
      if(ret_value < 0)
      {
        perror("\nERROR: FAILED TO WRITE MESSAGE TO DEVICE\n");
        return errno;
      }
    }
    else if(strncmp(recd_part1,"query",strlen("query")) == 0)
    {
      packet send;

      /*read the query from kernel space*/
      ret_value = read(fd,&send,sizeof(send));
      if(ret_value < 0)
      {
        perror("\nERROR: FAILED TO READ MESSAGE FROM DEVICE\n");
        return errno;
      }

      /*send the response for query to client*/
      write(newsockfd, &send,sizeof(send));
    }

  }

  /*close the file*/
  close(fd);
  return 0;

}
