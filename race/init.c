#include "defs.h"

void initRunner(RunnerType **runner, char *name, char *avatar, int column, int row){
    *runner = (RunnerType *) malloc(sizeof(RunnerType));
    strcpy((*runner)->name, name);
    strcpy((*runner)->ent.avatar, avatar);
    (*runner)->ent.path = column;
    (*runner)->ent.currPos = row;
    (*runner)->health = MAX_HEALTH;
    (*runner)->dead = 0;
  }

void addRunnerToArr(RunnerType **runner, int **runnerRank){
  race->runners[**runnerRank] = *runner;
  (**runnerRank)++;
  //pthread_t t;
  //(*runner)->ent.thr = t;
  race->numRunners += 1;
}

void initRace(){
  if(sem_init(&(race->mutex), 0, 1) < 0){
    printf("Semaphore initialization error\n");
    exit(1);
  }
  strcpy(race->winner, "");
  race->statusRow = 4;
  srand((unsigned)time(NULL));
  initNcurses();
  scrPrt("Health:", 0, 30);
  scrPrt("T", 0, 41);
  scrPrt("H", 0, 46);
  for(int i = 0; i < race->numRunners; i++){
    pthread_create(&(race->runners[i]->ent.thr), NULL, goRunner, race->runners[i]);
  }

}
