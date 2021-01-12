#include "defs.h"

void *goRunner(void *r){
  RunnerType *runner = &(*((RunnerType *) r));
  int flag = 1;


  if(runner->ent.currPos == 2 || runner -> dead == 1){
    flag = 0;
  }


  while(flag == 1){
    int step = 0;
    int ranNum = randm(10000);
    if(ranNum < 7000){
      step = -(randm(4)+1);
      if((runner->health)+step >=0){
        if(!(runner->health+step > 50)){
            (runner->health) += step;
        }

      }else{
        runner->health = 0;
        runner->dead = 1;
        flag = 0;
      }
    }
    else if(ranNum >= 7000){
      step = (randm(3)+1);
    }


    if(sem_wait(&(race->mutex)) < 0){
      printf("semaphore wait error\n");
      exit(1);
    }

    int newPos = 0;

    if((runner->ent.currPos + step)<=2){
      newPos = 2;
    }else{
      newPos = runner->ent.currPos + step;
    }

    for(int i = 0; i < race->numDorcs; i++){
      if((race->dorcs[i]->currPos == newPos) && (race->dorcs[i]->path == runner->ent.path)){
        char collision[70];
        sprintf(collision, "STATUS: collision between %s and dorc", runner->name);
        scrPrt(collision, race->statusRow, 30);
        race->statusRow += 1;
        runner->health -=3;
      }
    }

    if(sem_post(&(race->mutex)) < 0){
      printf("semaphore post error\n");
      exit(1);
    }






  if(runner->health == 0){
    strcpy(runner->ent.avatar, "+");
    runner->dead = 1;
    char status[50];
    sprintf(status, "STATUS:   %s is dead", runner->name);
    scrPrt(status, race->statusRow, 30);
    race->statusRow += 1;
    }

    //lock the semaphore
    if(sem_wait(&(race->mutex)) < 0){
      printf("semaphore wait error\n");
      exit(1);
    }

    scrPrt(" ", runner->ent.currPos, runner->ent.path);


    scrPrt(runner->ent.avatar, newPos, runner->ent.path);


    if(strcmp(runner->ent.avatar, "T")==0){
      if(runner->health < 10){
        char timmyHealth[2];
        sprintf(timmyHealth, "%d", runner->health);
        scrPrt(" ", 1, 41);
        scrPrt(" ", 1, 42);
        scrPrt(timmyHealth, 1, 41);
      }else{
        char timmyHealth[2];
        sprintf(timmyHealth, "%d", runner->health);
        scrPrt(timmyHealth, 1, 41);
      }

    }

    if(strcmp(runner->ent.avatar, "H")==0){

      if(runner->health < 10){
        char haroldHealth[2];
        sprintf(haroldHealth, "%d", runner->health);
        scrPrt(" ", 1, 46);
        scrPrt(" ", 1, 47);
        scrPrt(haroldHealth, 1, 46);
      }else{
          char haroldHealth[2];
          sprintf(haroldHealth, "%d", runner->health);
          scrPrt(haroldHealth, 1, 46);
        }
      }


    //unlock the semaphore
    if(sem_post(&(race->mutex)) < 0){
      printf("semaphore post error\n");
      exit(1);
    }

    //set runner's current position to new position
    if((runner->ent.currPos + step)<=2){
      flag = 0;
      runner->ent.currPos = 2;
    }else{
      runner->ent.currPos += step;
    }

    usleep(250000);

    //check loop condition
    if(runner->ent.currPos == 2 || runner -> dead == 1){
      flag = 0;
    }

  //set winner
  }

  if(runner->dead == 0){
    if(strcmp(race->winner, "")==0){
      strcpy(race->winner, runner->name);
    }
  }

  scrPrt(runner->ent.avatar, runner->ent.currPos, runner->ent.path);

}


void createRaceLoop(){


  race->numDorcs = 0;
  int flag = 1;


  if(strcmp(race->winner,"")!=0){
    flag = 0;
  }
  else{
    int deadNum = 0;
    for(int i = 0; i < race->numRunners; i++){
      if(race->runners[i]->dead == 1){
        deadNum++;
      }
    }
    if(deadNum == race->numRunners){
      flag = 0;
    }
  }




  while(flag == 1){

    int ran = randm(100);
    if(ran<30){
      EntityType *dorc = malloc(sizeof(EntityType));
      strcpy(dorc->avatar, "d\0");
      dorc -> currPos = 2;
      int ranNum = randm(3);
      if(ranNum == 0){
        dorc->path = 10;
      }else if(ranNum == 1){
        dorc->path = 12;
      }else if(ranNum == 2){
        dorc->path = 14;
      }

      race->dorcs[race->numDorcs] = dorc;
      (race->numDorcs) += 1;

      pthread_create(&(dorc->thr), NULL, goDorc, dorc);

      usleep(250000);

    }




    if(strcmp(race->winner, "") != 0){
      flag = 0;
    }
    else{
      int deadNum = 0;
      for(int i = 0; i < race->numRunners; i++){
        if(race->runners[i]->dead == 1){
          deadNum++;
        }
      }
      if(deadNum == race->numRunners){
        flag = 0;
      }
    }


  //terminate all dorc threads

  }
}


void *goDorc(void *d){

  EntityType *dorc = &(*((EntityType *) d));
  int flag = 1;


  if(dorc->currPos >= 35){
    flag = 0;
  }

  while(flag == 1){
    int step = randm(5)+1;


    int column = dorc->path;
    int move = randm(3);
    if(move == 0){
      column-=2;
    }else if(move == 2){
      column += 2;
    }

    if(column == 8){
      column = 10;
    }
    if(column == 16){
      column = 14;
    }

    //move dorc to new position
    if(sem_wait(&(race->mutex)) < 0){
      printf("semaphore wait error\n");
      exit(1);
    }

    scrPrt(" ", dorc->currPos, dorc->path);
    if((dorc->currPos+step)>=35){
      scrPrt(dorc->avatar, 35, column);
    }else{
      scrPrt(dorc->avatar, dorc->currPos+step, column);
    }



    if(sem_post(&(race->mutex)) < 0){
      printf("semaphore post error\n");
      exit(1);
    }



    if((dorc->currPos+step)>=35){
      dorc->currPos = 35;
    }else{
      dorc->currPos += step;
    }


    dorc->path = column;

    if(dorc->currPos >= 35){
      flag = 0;
    }


    usleep(700000);

  }

  scrPrt(" ", dorc->currPos, dorc->path);

}
