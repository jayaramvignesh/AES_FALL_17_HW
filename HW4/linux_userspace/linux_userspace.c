#include<unistd.h>
#include<math.h>
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

/*structure packet for command*/
typedef struct packet_info
{
  uint8_t led_state;
  uint8_t period;
  uint8_t dutycycle;
}packet;

int main(int argc, char* argv[])
{
  int sockfd, port_number, n;

  struct sockaddr_in server_address;
  struct hostent *server;

  /*check if port number and ip is provided*/
  if(argc<3)
  {
    printf("\nUSAGE %s hostname port\n",argv[0]);
    exit(1);
  }

  /*store the port number*/
  port_number = atoi(argv[2]);
  
  /*create a TCP socket*/
  sockfd = socket(AF_INET, SOCK_STREAM, 0);

  if(sockfd < 0)
  {
    printf("\nERROR: CREATING SOCKET\n");
    exit(1);
  }

  server = gethostbyname(argv[1]);

  if(server == NULL)
  {
    printf("\nERROR: NO SUCH HOST\n");
    exit(1);
  }

  bzero((char *)&server_address, sizeof(server_address));
  server_address.sin_family = AF_INET;
  bcopy((char *)server->h_addr, (char *)&server_address.sin_addr.s_addr, server->h_length);

  server_address.sin_port = htons(port_number);

  /*start a connection*/
  if(connect(sockfd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
  {
    printf("\nERROR: CONNECTION\n");
  }

  char array[20] = {};
  char arr[10] = {};
  packet send;
  uint32_t initial_period = 1;
  uint32_t initial_dutycycle = 50;
  while(1)
  {

    /*ask for command or query*/
    printf("\ncommand or query\n");
    scanf( "%[^\n]s",arr);
	  getchar();

    /*check if command or query*/
    if(strncmp(arr,"command",strlen("command")) == 0)
    {
      /*send to server*/
      write(sockfd,"command",strlen("command"));
      usleep(10000);

      /*print the options,take the command input and filename*/
  	  printf("\nOptions are\n");
      printf("1. state <ON/OFF>\n");
      printf("2. period <1-3>\n");
      printf("3. dutycycle <1-100>\n");

  	  printf("\nenter the option in the above mentioned format\n");
      scanf( "%[^\n]s",array);
	    getchar();
 
      /*check if command is state*/
      if(strncmp(array,"state",strlen("state")) == 0)
      {
        char *temp = strtok(array, " ");
        temp = strtok(NULL, " ");

        /*check if command state is ON or OFF*/
        if(strncmp(temp,"ON", strlen("ON")) == 0)
        {
          send.led_state = ON;
          send.period = 0;        //set default period to 0
          send.dutycycle = 0;     //set default dutycycle to 0
        }
        else if(strncmp(temp,"OFF", strlen("OFF")) == 0)
        {
          send.led_state = OFF;
          send.period = 0;        //set default period to 0
          send.dutycycle = 0;     //set default dutycyle to 0
        }
      }
      else if(strncmp(array,"period",strlen("period")) == 0)
      {
        char *temp = strtok(array, " ");
        temp = strtok(NULL, " ");
        int period_led = atoi(temp);    //convert period to int
        send.led_state = ON;
        send.period = period_led;         
        initial_period = period_led;
        send.dutycycle = initial_dutycycle;

      }
      else if(strncmp(array,"dutycycle",strlen("dutycycle")) == 0)
      {
        char *temp = strtok(array, " ");
        temp = strtok(NULL, " ");
        int duty_led = atoi(temp);    //convert duty cycle to integer
        if(duty_led < 0 || duty_led > 100)
        {
          printf("\nDuty cycle not within limits. Limits are 1-100. PLease try again\n");
          continue;
        }
        send.led_state = ON;
        send.period = initial_period;
        initial_dutycycle = duty_led; 
        send.dutycycle = duty_led; 
      }
      else
      { 
        printf("\nWrong commands entered. Please try again\n");
        continue;
      }

      printf("\nstate is %d\n",send.led_state);
      printf("\nperiod is %d\n",send.period);
      printf("\nduty cycle is %d\n",send.dutycycle);

      write(sockfd,&send,sizeof(send)); //send the command to server
    }
    else if(strncmp(arr,"query" , strlen("query")) == 0 )
    {
      packet received;
      write(sockfd,"query",strlen("query"));  //send query to server
      usleep(100000);

      /*print the options,take the command input and filename*/
  	  printf("\nOptions are\n");
      printf("1. state\n");
      printf("2. period\n");
      printf("3. dutycycle\n");
      printf("4. all\n");

  	  printf("\nenter the option in the above mentioned format\n");
      scanf( "%[^\n]s",array);
	    getchar();

      /*check for different queries*/
      if(strncmp(array,"state",strlen("state")) == 0)
      {
        /*receive struct from server and check led state*/
        read(sockfd,&received,sizeof(received));
        if(received.led_state == 1)
        {
          printf("\nstate is ON\n");
        }
        else if(received.led_state == 2)
        {
          printf("\nstate is OFF \n");
        }
      }
      else if(strncmp(array,"period",strlen("period")) == 0)
      {
        /*receive struct from server and check period*/
        read(sockfd,&received,sizeof(received));
        printf("\nperiod is %d\n",received.period);
      
      }
      else if(strncmp(array,"dutycycle",strlen("dutycycle")) == 0)
      {
        /*receive struct from server and check dutycycle*/
        read(sockfd,&received,sizeof(received));
        printf("\ndutycycle is %d percent\n",received.dutycycle);
      }
      else if(strncmp(array,"all",strlen("all")) == 0)
      {
        /*receive struct from server and print all members*/
        read(sockfd,&received,sizeof(received));
        if(received.led_state == 1)
        {
          printf("\nstate is ON\n");
        }
        else if(received.led_state == 2)
        {
          printf("\nstate is OFF \n");
        }
        printf("\nperiod is %d\n",received.period);
        printf("\ndutycycle is %d percent\n",received.dutycycle);

      }
      else
      { 
        printf("\nWrong commands entered. Please try again\n");
        continue;
      }


    }

  }
}
