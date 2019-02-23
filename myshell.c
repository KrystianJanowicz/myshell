#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <grp.h>
#include <pwd.h>
#include <string.h>
#include <time.h>
#define BUFFERSIZE 255
#define BLU   "\x1B[34m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define RESET "\x1B[0m"

void help(){
  printf(BLU " Krystian Janowicz \n Available commands: \n echo [arg] \n pwd \n cd [arg] \n clear \n date \n help \n exit \n ls \n" RESET);
}

void clear(){
  printf("\033[H\033[J");
}

void pwd(){
  char path[BUFFERSIZE];
  getcwd(path,BUFFERSIZE);
  printf(GRN " %s" RESET,path);
}

void date(){
    time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char s[64];
    strftime(s, sizeof(s), "%c", tm);
    printf("%s\n", s);
}

void prompt(){
  char *user;
  char *path;
  char hostname[BUFFERSIZE];

  user = getenv( "USER" );
  memset(hostname, 0, BUFFERSIZE);
  gethostname(hostname, BUFFERSIZE);
  printf(YEL "%s@" RESET, user);
  printf(YEL "%s" RESET, hostname);
  pwd();
  printf(" $ ");
  }

int echo(char command[BUFFERSIZE]){
  char *checkThatSign = " ";
  int lenght=strlen(command);
  for(int i=0;i<=lenght-1; i++){

    char temp;
    temp=command[i];

    if(temp==' '){
        char *rest = strpbrk(command, checkThatSign);
        printf("%s", rest);
        return 0;
      }
  }
}

int exxit(char command[BUFFERSIZE]){

    char *checkThatSign = " ";
    int lenght=strlen(command);
    char temp;

for(int i=0;i<=lenght-1; i++){

    temp=command[i];

    if(temp==' '){
          return command[i+1]-48;
        }
    }
      return 0;
}

void cd(char command[BUFFERSIZE]){
    char *temp;
    temp = strchr(command,' ');

        temp = temp+1;
        char *locationOfNewLine = strchr(temp, '\n');
        if(locationOfNewLine) {
            *locationOfNewLine = '\0';
        }
        chdir(temp);
}

void ls(char *name) {
  DIR *dir;
   struct dirent *dp;
   struct stat statbuf;

   if ((dir = opendir(name)) == NULL) {
     perror("Blad");
   }
   while ((dp = readdir(dir)) != NULL) {
     if (stat(dp->d_name, &statbuf) == -1) continue;
 	if (dp->d_name[0] == '.') continue;

     printf(  "%s  ", dp->d_name);
   }
   closedir(dir);
}

int main() {

  char command[BUFFERSIZE];

  do{
    prompt();
    bzero(command, BUFFERSIZE);
    fgets(command, BUFFERSIZE, stdin);

      if (strcmp(command, "help\n") == 0){  help();  }
        else if (strcmp(command, "ls\n") == 0){
          ls(".");
          printf("\n");
        }
        else if (strcmp(command, "pwd\n") == 0){
          pwd();
          printf("\n");
        }
        else if (strcmp(command, "date\n") == 0){  date();  }
        else if (strcmp(command, "clear\n") == 0){  clear();  }
        else if((command[0]=='c') && (command[1]=='d')) {  cd(command); }
        else if ((command[0]=='e') && (command[1]=='c') && (command[2]=='h') && (command[3]=='o')){  echo(command); }
        else if ((command[0]=='e') && (command[1]=='x') && (command[2]=='i') && (command[3]=='t')){   return exxit(command);  }
        else{ printf ("ERROR: didn't found that command, try 'help' \n" ) ;  }

  }while(1);

}
