#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h>
#include <string.h>

int main(){
  key_t key;
  int shmid;
  char * data;

  key = ftok("foo", 'R');
  shmid = shmget(key, 1024, 0644 | IPC_CREAT);
  data = shmat(shmid, (void *) 0, 0);

  if(data[0])
    printf("contents: %s \n", data);
  else
    printf("created \n");

  printf("change contents? ");
  char input[100];
  fgets(input,100,stdin);
  if(! strcmp(input, "yes\n")){
    printf("new string: ");
    fgets(input,100,stdin);
    input[strlen(input) - 1] = 0;
    strcpy(data,input);
  }

  printf("delete contents? ");
  fgets(input,100,stdin);
  if(! strcmp(input, "yes\n")){
    shmdt(data);
    shmctl(shmid, IPC_RMID, NULL);
    printf("  deleted \n");
  }

  return 0;
}
