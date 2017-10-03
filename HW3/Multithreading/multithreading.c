#define _POSIX_C_SOURCE 199506L

#include <errno.h>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include<stdbool.h>
#include <ctype.h>

#define MAX_WORD_SIZE 100
#define MAX_WORDS 1024
#define FREQ_CNT 5
#define SIZE 1024
char filename[100] = "";

/*structure to store the calculate statistics of file read*/
typedef struct
{
  int line_cnt;
  int char_cnt;
  int word_cnt;
  int no_top_repeated_words;
}file_stats;

/*structure for frequenct word info*/
typedef struct words_1
{
  char s[MAX_WORD_SIZE];
  int freq;
}word_map;

/*create a structure instance for the word frequency*/
word_map words[MAX_WORDS];


/*create a global structure instance*/
file_stats statistics;

pthread_t th1_id, th2_id;

/*create a global file pointer*/
FILE *fp;
pthread_mutex_t file_lock;
pthread_mutex_t count_lock;

/*function to insert a word into structure. and increment count of word if already present*/
void word_insert(word_map *words, int* no_of_words, char *c)
{

  /*search if word is present nad if yes increment freq*/
  for(int i = 0; i< *no_of_words; i++)
  {
    if(strcmp(c,words[i].s) == 0)
    {
      words[i].freq++;
      return;
    }
  }

  /*check for error conditions*/
  if(strlen(c) >= MAX_WORD_SIZE)
  {
    printf("\nWORD IS TOO LONG\n");
    exit(1);
  }

  if(*no_of_words >= MAX_WORDS)
  {
    printf("\nTOO MANY WORDS\n");
    exit(1);
  }

  /*if word is not present, add to the structure*/
  strcpy(words[*no_of_words].s,c);
  
  /*since new word,make freq 1*/
  words[*no_of_words].freq = 1;

  /*increment number of words*/
  (*no_of_words)++;
}

/*sort the words in descending order*/
int word_sort(word_map *first, word_map *second)
{
  if(first->freq < second->freq)
    return +1;
  
  if(first->freq > second->freq)
    return -1;
}

/*check if alphabets*/
int check_alphabets(char c)
{ 
  if(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z')
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

/*function to remove the nth character from a string*/
void remove_character(char *c, int n)
{
  while(c[n])
  {
    n++;
    c[n-1] =c[n];
  }
  c[n] = 0;
}

/*remove non alphabetic characters*/
void remove_non_alphabetic(char *c)
{
  int i;
  for( i = 0; c[i]; i++)
  {
    if(check_alphabets(c[i]) == 0)
    {
      remove_character(c,i);
    }
  }
}

/*make all letters lowercase*/
void lowercase_words(char *c)
{
  int i;
  for(i=0; c[i]; i++)
  {
    c[i] = tolower(c[i]);
  }
}


/*Signal handler for SIGINT*/
void signal_handler()
{
  /*destroy both the mutex*/
  pthread_mutex_destroy(&count_lock);
  pthread_mutex_destroy(&file_lock);
 
  /*exit from both the pthreads*/
  pthread_exit(NULL);
  pthread_exit(NULL);

  printf("\nBYE BYE!! END OF PROGRAM!!\n");
  
  /*exit from the main program*/
  exit(1);
}

/*Signal handler for SIGUSR1*/
static void sigusr1_handler(int sig)
{
    printf("\nINSIDE SIGUSR1 SIGNAL HANDLER\n");
    char ch;
    
    /*lock the mutex*/
    pthread_mutex_lock(&file_lock);
    pthread_mutex_lock(&count_lock);
 
    printf("\nFILE MUTEX LOCKED INSIDE SIGUSR1\n");
    printf("\nWORD MUTEX LOCKED INSIDE SIGUSR1\n");
   
    /*check if file pointer is NULL*/
    if(fp == NULL)
    {
      printf("\nFILE NOT FOUND\n");
    }
    else
    {
      /*bring the file pointer back to the starting of file*/
      rewind(fp);

      /*Read the file character by character until end of file*/
      while((ch = getc(fp)) != EOF)
      {
        /*increment the character count*/
        ++statistics.char_cnt;
      
        /*if space or end of line is encountered, increment word count*/
        if(ch == ' ' || ch == '\n')
        {
          ++statistics.word_cnt;
        }

        /*if end of line is encountered, increment line count*/
        if(ch == '\n')
        {
          ++statistics.line_cnt;
        }
      }
    
      /*rewind file pointer to start of function*/
      rewind(fp);
      char input_word[1000];
      int i,no_of_words;

      no_of_words = 0;
      while(fscanf(fp,"%1023s",input_word) == 1)
      {
        if(check_alphabets(input_word[0]))
        {
          remove_non_alphabetic(input_word);
          lowercase_words(input_word);
          word_insert(words,&no_of_words,input_word);
        }
      }

     qsort((void *)words, no_of_words ,sizeof(word_map),word_sort);

    if(no_of_words < FREQ_CNT)
    {
      statistics.no_top_repeated_words = no_of_words;
    }
    else
    {
      statistics.no_top_repeated_words = FREQ_CNT;
    }

    
  }
    
    /*unlock the mutex*/
    pthread_mutex_unlock(&file_lock);
    pthread_mutex_unlock(&count_lock);
    printf("\nFILE MUTEX UNLOCKED INSIDE SIGUSR1\n");
    printf("\nWORD MUTEX UNLOCKED INSIDE SIGUSR1\n");
}

/*function for thread 1*/
void *thread1_function(void *param)
{
  int status;
  while(1)
  {
    sigset_t set;
    int set1 = 0;
    
//    sigfillset(&set);
    /*add SIGUSR1 to the set*/
    if(sigaddset(&set,SIGUSR1) == -1)
    {
      perror("Sigaddset error");
      pthread_exit((void *)1);
    }

    /*wait here till signal is received*/
    sigwait(&set,&set1);

    /*if signal is SIGUSR1 then goto handler*/
    if(set1  == SIGUSR1)
    {
      sigusr1_handler(set1);
    }
    
    printf("\nRETURNED AFTER SIGUSR1 HANDLER\n");
  
    /*calling pthread kill*/
    status = pthread_kill(th2_id, SIGUSR2);
  
    if(status < 0)
    {
      perror("ERROR: PTHREAD KILL");
    }
  
  }
}

/*Handler for SIGUSR2*/
static void sigusr2_handler(int sig)
{
    printf("\nINSIDE SIGUSR2 SIGNAL HANDLER\n");
 
    /*lock the word mutex*/
    pthread_mutex_lock(&count_lock);
    
    printf("\nWORD MUTEX LOCKED INSIDE SIGUSR2\n");

    /*print the statistics*/
    printf("\nLine Count is %d\n",statistics.line_cnt);
    printf("\nword Count is %d\n",statistics.word_cnt);
    printf("\nchar Count is %d\n",statistics.char_cnt);
    
    printf("\nTOP 5 repeated words are\n");
    for(int i = 0; i<statistics.no_top_repeated_words; i++)
    {
      printf("%s\t%d\n",words[i].s,words[i].freq);
    }
    /*reset them to zero*/
    statistics.line_cnt = 0;
    statistics.word_cnt = 0;
    statistics.char_cnt = 0;
    statistics.no_top_repeated_words = 0;
    /*unlock the mutex*/
    pthread_mutex_unlock(&count_lock);

    printf("\nWORD MUTEX UNLOCKED INSIDE SIGUSR2\n");
}

/*function for thread 2*/
void *thread2_function(void *param)
{
  int status;
 
  while(1)
  {
    sigset_t set;
    int set1 = 0;

    /*add SIGUSR2 to set*/
    if(sigaddset(&set,SIGUSR2) == -1)
    {
      perror("Sigaddset error");
      pthread_exit((void *)1);
    }
   
    /*wait for signal SIGUSR2*/
    sigwait(&set,&set1);
    if(set1  == SIGUSR2)
    {
      sigusr2_handler(set1);
    } 
 
    printf("\nRETURNED AFTER SIGUSR2 HANDLER\n");
  
  }
  
}

int main()
{ 
  int th_param = 1;
  int status;
  int thread_status;

  /*signal_handler for SIGINT*/
  signal(SIGINT,signal_handler);
  
  sigset_t sigmask;
  struct sigaction action;
  int set1 = 0;
  
  /*get pid of current process*/
  pid_t p;
  p = getpid();
  printf("\nPID i %d\n",p);

  /*set up signal mask to block all in main thread*/
  sigfillset(&sigmask);
  pthread_sigmask(SIG_BLOCK, &sigmask, (sigset_t *)0);

  /*Set up signal handlers for SIGUSR1*/
  action.sa_flags = 0;
  action.sa_handler = sigusr1_handler;
  sigaction(SIGUSR1, &action, (struct sigaction *)0);
  action.sa_handler = sigusr2_handler;
  sigaction(SIGUSR2, &action, (struct sigaction *)0);
 
  /*take filename from user*/
  printf("\nPlease give the filename\n");
  scanf("%s%*c",filename);
  printf("\nFilename is %s\n",filename);
  
  /*open file name for write and append*/
  char *ptr;
  char buffer[SIZE];
  ptr = buffer;
  fp = fopen(filename,"w+");

  /*create threads*/
  status = pthread_create(&th1_id,NULL,thread1_function,(void *)&th_param);
  if(status < 0)
  {
    perror("\nERROR: PTHREAD CREATION\n");
    exit(1);
  }
 
  status = pthread_create(&th2_id,NULL,thread2_function,(void *)&th_param);
  if(status < 0)
  {
    perror("\nERROR: PTHREAD CREATION\n");
    exit(1);
  } 
  printf("\ncreated pthread\n");
  
  sleep(0.5);

  while(1)
  {
    pthread_mutex_lock(&file_lock);
    printf("\nFILE MUTEX LOCKED INSIDE MAIN\n");
    
    printf("\nWrite to the given file\n\n");
    int len = 0;
    char c;
  
    /*take input from user for file till ctrl+d*/
    while(fgets(ptr,SIZE,stdin)!=NULL)
    {
      len = strlen(ptr);
      fwrite(buffer,1,len,fp);
      sleep(0.5);
      len = 0;
      signal(SIGQUIT,signal_handler);
    }
    pthread_mutex_unlock(&file_lock);
    printf("\nFILE MUTEX UNLOCKED INSIDE MAIN\n");

    sleep(1);
    /*calling pthread kill*/
    status = pthread_kill(th1_id, SIGUSR1);
    sleep(2);
    if(status < 0)
    {
      perror("ERROR: PTHREAD KILL");
    }
  }
}
