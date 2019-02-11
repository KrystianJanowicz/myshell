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
  printf(BLU " Krystian Janowicz \n Dostepne polecenia: \n echo [arg] \n pwd \n help \n exit \n ls \n" RESET);
}

void pwd(){
  char path[BUFFERSIZE];
  getcwd(path,BUFFERSIZE);
  printf(GRN " %s" RESET,path);
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

int echo(char komenda[BUFFERSIZE]){
  char *sprawdzczy = " ";
  int dlugosc=strlen(komenda);
  for(int i=0;i<=dlugosc-1; i++){

    char temp;
    temp=komenda[i];

    if(temp==' '){
        char *reszta = strpbrk(komenda, sprawdzczy);
        printf("%s", reszta);
        return 0;
      }
  }
}

int exxit(char komenda[BUFFERSIZE]){
char *sprawdzczy = " ";
int dlugosc=strlen(komenda);
for(int i=0;i<=dlugosc-1; i++)
{

char temp;
temp=komenda[i];
char *sprawdzczy = " ";
if(temp==' '){

char *reszta = strpbrk(komenda, sprawdzczy);
int dlugoscReszty=strlen(reszta)-1;
printf("%d\n", dlugoscReszty);
int zwrocik=reszta[1];
return zwrocik-48; // -48 bo ASCII, nie wiedzialem jak to przekonwertowac "normalnie"
}

}
return 0;

}
void cd(char komenda[BUFFERSIZE]){
  char *tok;
    tok = strchr(komenda,' ');

        char *tempTok = tok + 1;
        tok = tempTok;
        char *locationOfNewLine = strchr(tok, '\n');
        if(locationOfNewLine) {
            *locationOfNewLine = '\0';
        }
        chdir(tok);
}


void list_dir(char *name) {
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

int main(int argc, char **argv) {

  char komenda[BUFFERSIZE];

  do{
    prompt();
    bzero(komenda, BUFFERSIZE);
    fgets(komenda, BUFFERSIZE, stdin);

      if (strcmp(komenda, "help\n") == 0){
          help();
        }
        else if (strcmp(komenda, "ls\n") == 0){
          chdir(*(++argv));
          list_dir(".");
            printf("\n");
        }
        else if (strcmp(komenda, "pwd\n") == 0){
          pwd() ;
          printf("\n");
        }
        else if((komenda[0]=='c') && (komenda[1]=='d')) {
            cd(komenda);

        }else if ((komenda[0]=='e') && (komenda[1]=='c') && (komenda[2]=='h') && (komenda[3]=='o')){

          echo(komenda);
        }
        else if ((komenda[0]=='e') && (komenda[1]=='x') && (komenda[2]=='i') && (komenda[3]=='t')){
          int zwrot=exxit(komenda);
          return zwrot;
        }
        else{
        printf ("nie znaleziono polecenia. uzyj: help \n" ) ;
        }

  }while(1);

}
