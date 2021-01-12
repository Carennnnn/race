#include "defs.h"

int main(){

  race = (RaceInfoType *) malloc(sizeof(RaceInfoType));
  RunnerType *timmy;
  RunnerType *harold;

  initRunner(&timmy, "Timmy", "T", 10, 35);
  initRunner(&harold, "Harold", "H", 14, 35);

  int *runnerRank;
  runnerRank = (int*) malloc(sizeof(int));
  *runnerRank = 0;
  race->numRunners = 0;
  addRunnerToArr(&timmy, &runnerRank);
  addRunnerToArr(&harold, &runnerRank);

  initRace();

  createRaceLoop();

  //wait until all runner s=threads ends normally

  for(int i = 0; i < race->numRunners; i++){
    pthread_join(race->runners[i]->ent.thr, NULL);
  }


  char outcome[70];
  sprintf(outcome, "OUTCOME: The winner is %s", race->winner);
  scrPrt(outcome, race->statusRow, 30);


  return 0;
}
