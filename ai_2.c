#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
#include <unistd.h>

#define BASE 65 // 65 is A in ASCI

int **states;
int *visited;
int *active;
int *path;
int *code;
float *cost;
float *heuristic[2];

int UCS_expansions = 0;
int Astar_expansions = 0;

float UCS_cost = 0;
float Astar_cost = 0;


int astar(int ak, int tk1, int tk2, int size, int length){
  int state, counter;
  int i, j, in_active, active_index;
  int index_min, value_min;

  // Heuristic fucntion
  float h(float h1, float h2){
    if(h1 < h2){
      return h1;
    }
    return h2;
  }

  active_index = 0;
  active[active_index] = ak;
  in_active = 1;
  cost[ak] = 0;
  path[ak] = -1;
  value_min = size;
  index_min = ak;

  for (i = 0; i < size; i++) {
    for (j = 0; j < length; j++) {
      if(states[i][j]!=states[tk1][j]){
        if(i<(length/2)){
          heuristic[0][i] += 1;
        }else{
          heuristic[0][i] += 0.5;
        }
      }
      if(states[i][j]!=states[tk2][j]){
        if(i<(length/2)){
          heuristic[1][i] += 1;
        }else{
          heuristic[1][i] += 0.5;
        }
      }
    }
  }


  while (in_active > 0 && index_min != tk1 && index_min != tk2) {
    // Search in Cost for minimum
    for(i = 0; i < size; i++) {
      if(cost[i] + h(heuristic[0][i],heuristic[1][i]) < value_min){
        value_min = cost[i];
        index_min = i;
      }
    }

    // Search in States for neighboors
    int tmp, put_it, count;
    for(i = 0; i < size; i++) {
      counter = 0;
      if(visited[i] == 0) {
        for(j = 0; j < length; j++) {
          if(states[i][j] != states[index_min][j]) {
            counter++;
            tmp = j;
          }
        }
        put_it = 1;
        count = active_index;
        if(counter == 1){
          while (count >= 0) {
            if(i == active[count]){ // If this neighboor is already in active board
              put_it = 0; // Do NOT put it in.
            }
            count--;
          }
          if(put_it == 1){
            //Update active board
            active[++active_index] = i;
            in_active++;
            Astar_expansions++;
            //Update path board
            path[i] = index_min;
            //Update cost board
            if(tmp < length/2){
              cost[i] = cost[index_min] + 1;
            }else{
              cost[i] = cost[index_min] + 0.5;
            }
          }
        }
      }
    }

    Astar_cost = cost[index_min];
    cost[index_min] = size;
    value_min = size;

    //Update visited board
    visited[index_min] = 1;

    //Update active board
    active[index_min] = -1;
    in_active--;
  }


  if (in_active <= 0) {
    return -1;
  }
  return index_min;
}



int ucs(int ak, int tk1, int tk2, int size, int length){
  int state, counter;
  int i, j, in_active, active_index;
  int index_min, value_min;

  active_index = 0;
  active[active_index] = ak;
  in_active = 1;
  cost[ak] = 0;
  path[ak] = -1;
  value_min = size;
  index_min = ak;


  while (in_active > 0 && index_min != tk1 && index_min != tk2) {
    // Search in Cost for minimum
    for (i = 0; i < size; i++) {
      if(cost[i] < value_min){
        value_min = cost[i];
        index_min = i;
      }
    }

    // Search in States for neighboors
    int tmp, put_it, count;
    for(i = 0; i < size; i++) {
      counter = 0;
      if(visited[i] == 0) {
        for(j = 0; j < length; j++) {
          if(states[i][j] != states[index_min][j]) {
            counter++;
            tmp = j;
          }
        }
        put_it = 1;
        count = active_index;
        if(counter == 1){
          while (count >= 0) {
            if(i == active[count]){ // If this neighboor is already in active board
              put_it = 0; // Do NOT put it in.
            }
            count--;
          }
          if(put_it == 1){
            //Update active board
            active[++active_index] = i;
            in_active++;
            UCS_expansions++;
            //Update path board
            path[i] = index_min;
            //Update cost board
            if(tmp < length/2){
              cost[i] = cost[index_min] + 1;
            }else{
              cost[i] = cost[index_min] + 0.5;
            }
          }
        }
      }
    }

    UCS_cost = cost[index_min];
    cost[index_min] = size;
    value_min = size;

    //Update visited board
    visited[index_min] = 1;

    //Update active board
    active[index_min] = -1;
    in_active--;
  }


  if (in_active <= 0) {
    return -1;
  }
  return index_min;
}


int main(){

  int i, k, j, L, M, d, tmp;
  long int N;
  int ucs_tk;
  int astar_tk;

  //Initialize L
  do{
    printf("Give the amount of letters between 1 and 9\nL : ");
    scanf("%d", &L);
  }while(L>=10||L<0);

  //Initialize M
  do{
    printf("Give the amount of numbers between 1 and 9\nM : ");
    scanf("%d", &M);
  }while(M>=10||M<0);

  //Initialize d
  printf("Give the length of the word\nd : ");
  scanf("%d", &d);
  while (d % 2 == 1) {
    printf("Length of the word must be even number\nTry again!\nd : ");
    scanf("%d", &d);
  }

  //Initialize N
  printf("Give the number of possible situations\nN : ");
  scanf("%ld", &N);
  long int maxN = (pow(L,(d/2)))*(pow(M,(d/2)));
  while(!(N < maxN && N > 3)) {
    printf("Number of possible situations must be between 3 - %ld\nN : " , maxN-1);
    scanf("%ld", &N);
  }

  //Initialize states
  states = (int **) malloc(N*sizeof(int *));
  for (i=0; i<N; i++){
    states[i] = (int *)malloc(d * sizeof(int));
  }

  //Initialize helper boards
  visited = (int*) calloc(N, sizeof(int));
  active = (int*) malloc(N* sizeof(int));
  path = (int*) calloc(N, sizeof(int));
  code = (int*) calloc(N, sizeof(int));
  cost = (float*) malloc(N* sizeof(float));
  heuristic[0] = (float*) malloc(N* sizeof(float));
  heuristic[1] = (float*) malloc(N* sizeof(float));

  for (i = 0; i < N; i++) {
    cost[i] = N;
    active[i] = -1;
  }

  //Initialize rand generator
  time_t t;
  srand((unsigned) time(&t));

  int input = 0;
  int dif = 0;
  int dif_with_all = 0;
  while(input<N){

    // Product new State
    for(i = 0; i < d; i++){
      if(i < (d/2)){
        code[i] = BASE + (rand() % L);
      }else{
        code[i] =( rand() % M);
      }
    }

    // Check if already exists
    dif_with_all = 0;
    for(i = 0; i < input ; i++){
      dif = 0;
      for(j = 0; j < d; j++){
        if(states[i][j] != code[j]){
          dif = 1;
        }
      }
      if(dif == 1){
        dif_with_all ++;
      }
    }

    if(dif_with_all == input){
      for(j = 0; j < d; j++){
        states[input][j] = code[j];
      }
      input ++;
    }

  }
  for ( k = 0; k < N; k++) {
    for(i=0;i<d;i++){
      if(i<(d/2)){
        printf("%c ",states[k][i]);
      }else{
        printf("%d ",states[k][i]);
      }
    }
    printf("\n");
  }

  int ak,tk1,tk2;
  do {
    printf("\n");
    printf("Give me a number from 0 to %ld as a initial situation: \n", N-1);
    scanf("%d", &ak);
  } while(ak < 0 || ak > N-1);
  for(i=0;i<d;i++){
    if(i<(d/2)){
      printf("%c ",states[ak][i]);
    }else{
      printf("%d ",states[ak][i]);
    }
  }

  do {
    printf("\n");
    printf("Give me a number from 0 to %ld as one of the final situations: \n", N-1);
    scanf("%d", &tk1);
  } while(tk1 < 0 || tk1 > N-1);
  for(i=0;i<d;i++){
    if(i<(d/2)){
      printf("%c ",states[tk1][i]);
    }else{
      printf("%d ",states[tk1][i]);
    }
  }

  do {
    printf("\n");
    printf("Give me a number from 0 to %ld as another final situation: \n", N-1);
    scanf("%d", &tk2);
  } while(tk2 < 0 || tk2 > N-1);
  for(i=0;i<d;i++){
    if(i<(d/2)){
      printf("%c ",states[tk2][i]);
    }else{
      printf("%d ",states[tk2][i]);
    }
  }
  printf("\n\n\n");


  ucs_tk = ucs(ak,tk1,tk2,N,d);
  printf("\n======= Unifor Cost Search =======\n");
  if(ucs_tk != -1){
    printf("\nSolution is state : ");
    for (i = 0; i < d; i++) {
      if(i < d/2){
        printf("%c", states[ucs_tk][i]);
      }else{
        printf("%d", states[ucs_tk][i]);
      }
    }
    printf("\nUCS_expansions : %d\n" , UCS_expansions);
    printf("Total cost : %.1f\n", UCS_cost );
    printf("Path :\n");

    tmp = ucs_tk;
    while(tmp != -1){
      for (i = 0; i < d; i++) {
        if(i < d/2){
          printf("%c", states[tmp][i]);
        }else{
          printf("%d", states[tmp][i]);
        }
      }
      printf("\n");
      tmp = path[tmp];
    }
  }else{
    printf("\nThere is no solution!\n");
  }

  printf("\n==================================\n");

  // Re-initialize
  for (i = 0; i < N; i++) {
    cost[i] = N;
    active[i] = -1;
    visited[i] = 0;
    path[i] = 0;
  }


  printf("\n========== A* Search =============\n");
  astar_tk = astar(ak,tk1,tk2,N,d);

  if(astar_tk != -1){
    printf("\nSolution is state : ");
    for (i = 0; i < d; i++) {
      if(i < d/2){
        printf("%c", states[astar_tk][i]);
      }else{
        printf("%d", states[astar_tk][i]);
      }
    }
    printf("\nAstar_expansions : %d\n" , Astar_expansions);
    printf("Total cost : %.1f\n", Astar_cost );
    printf("Path :\n");

    tmp = astar_tk;
    while(tmp != -1){
      for (i = 0; i < d; i++) {
        if(i < d/2){
          printf("%c", states[tmp][i]);
        }else{
          printf("%d", states[tmp][i]);
        }
      }
      printf("\n");
      tmp = path[tmp];
    }
  }else{
    printf("\nThere is no solution!\n");
  }

  printf("\n==================================\n");
  printf("UCS_expansions - Astar_expansions = %d\n", (UCS_expansions - Astar_expansions) );
  //printf("\nAstar_expansions : %d\n" , Astar_expansions);
  //printf("\nUCS_expansions : %d\n" , UCS_expansions);

  return 0;
}
