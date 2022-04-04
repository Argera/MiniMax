#include <stdio.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define K1 3  // red
#define K2 2  // green
#define K3 2  // yellow
#define M 5   // # of balls for each color

int turn = 0;
int board[3] = {M , M , M};

int win(const int board[3], int turn) {
  int i, j;
  int sum;
  sum = board[0] + board[1] + board[2];
  if((board[0]==K1 && sum==K1) || (board[1]==K2 && sum==K2) || (board[2]==K3 && sum==K3) || (sum == 1) ){
    if(turn % 2 == 0){
      return 1;
    }else{
      return -1;
    }
  }
  return 0;
}

int minimax(int board[3],int player){
 int move = -1;
 int score = -2;
 int i, j;
 int winner = win(board,turn);
 if(winner!=0){
  return winner*player;
 }

 for(i = 0; i < 4; ++i) {
    switch(i) {
      case 1:
        if(board[0] >= K1){
          board[0] -= K1;
          int tempScore = -minimax(board, (player*(-1)));
          board[0] += K1;
          if(tempScore > score) {
            score = tempScore;
            move = i;
          }
        }
        break;
      case 2:
        if(board[1] >= K2){
          board[1] -= K2;
          int tempScore = -minimax(board,player* -1);
          board[1] += K2;
          if(tempScore > score) {
            score = tempScore;
            move = i;
          }
        }

        break;
      case 3:
        if(board[2] >= K3){
          board[2] -= K3;
          int tempScore = -minimax(board, player*-1);
          board[2] += K3;
          if(tempScore > score) {
            score = tempScore;
            move = i;
          }
        }

        break;
      case 0:
          for(j = 4; j < 7; ++j) {
            switch(j) {
              case 4:
                if(board[0] >= 1){
                    board[0] -= 1;
                    int tempScore = -minimax(board, player*-1);
                    board[0] += 1;
                    if(tempScore > score) {
                        score = tempScore;
                        move = 4;
                    }
                }
                break;
              case 5:
                if(board[1] >= 1){
                  board[1] -= 1;
                  int tempScore = -minimax(board, player*-1);
                  board[1] += 1;
                  if(tempScore > score) {
                    score = tempScore;
                    move = 5;
                  }
                }
                break;
              case 6:
                if(board[2] >= 1){
                  board[2] -= 1;
                  int tempScore = -minimax(board, player*-1);
                  board[2] += 1;
                  if(tempScore > score) {
                    score = tempScore;
                    move = 6;
                  }
                }
                break;
            } // end of little switch
          } /// end of loop
      break; // break from case 0;
    } // end of big switch
  } // end of outer loop

  if(move == -1){
   return 0;
  }
  return score;

}


void computerMove(int board[3]) {

  int move = -1;
  int score = -2;
  int i, j;
  for(i = 3; i >= 0; i--) {
    switch(i) {
      case 1:
        if(board[0] >= K1){
          board[0] -= K1;

          int tempScore = -minimax(board, -1);
          board[0] += K1;
          if(tempScore > score) {
            score = tempScore;
            move = i;
          }
        }
      break;
      case 2:
        if(board[1] >= K2){
          board[1] -= K2;
          int tempScore = -minimax(board, -1);
          board[1] += K2;
          if(tempScore > score) {
            score = tempScore;
            move = i;
          }
        }

      break;
      case 3:
        if(board[2] >= K3){
          board[2] -= K3;
          int tempScore = -minimax(board, -1);
          board[2] += K3;
          if(tempScore > score) {
            score = tempScore;
            move = i;
          }
        }

      break;
      case 0:
      for(j = 1; j <= 3; ++j) {
        switch(j) {
          case 1:
          if(board[0] >= 1){
            board[0] -= 1;
            int tempScore = -minimax(board, -1);
            board[0] += 1;
            if(tempScore > score) {
              score = tempScore;
              move = 4;
            }
          }
          break;
          case 2:
            if(board[1] >= 1){
              board[1] -= 1;
              int tempScore = -minimax(board, -1);
              board[1] += 1;
              if(tempScore > score) {
                score = tempScore;
                move = 5;
              }
            }

          break;
          case 3:
            if(board[2] >= 1){
              board[2] -= 1;
              int tempScore = -minimax(board, -1);
              board[2] += 1;
              if(tempScore > score) {
                score = tempScore;
                move = 6;
              }
            }
        }
      }
      break;
    }
  }


  switch(move){
    case 1:
      board[0]-=K1;
      printf("Computer took %d "ANSI_COLOR_RED" red cubes\n" ANSI_COLOR_RESET,K1);
    break;
    case 2:
      board[1]-=K2;
      printf("Computer took %d "ANSI_COLOR_GREEN" green cubes\n" ANSI_COLOR_RESET,K2);
    break;
    case 3:
      board[2]-=K3;
      printf("Computer took %d "ANSI_COLOR_YELLOW" yellow cubes\n" ANSI_COLOR_RESET,K3);
    break;
    case 4:
      board[0]-=1;
      printf("Computer took 1 "ANSI_COLOR_RED" red cube\n" ANSI_COLOR_RESET);
    break;
    case 5:
      board[1]-=1;
      printf("Computer took 1 "ANSI_COLOR_GREEN" green cube\n" ANSI_COLOR_RESET);
    break;
    case 6:
      board[2]-=1;
      printf("Computer took 1 "ANSI_COLOR_YELLOW" yellow cube\n" ANSI_COLOR_RESET);
    break;

  }
  turn++;
}

void playerMove(int board[3]) {
  int move = -2;
  int i;

  do {
    if (move == -1){
        printf("\nGive a number between 0..3\n");
    }
    printf(ANSI_COLOR_RED "\n%d " ANSI_COLOR_GREEN "%d " ANSI_COLOR_YELLOW "%d\n" ANSI_COLOR_RESET, board[0], board[1], board[2]);
    printf("\nMove 0  : Take one cube of any color ");
    printf("\nMove 1  : Take %d "ANSI_COLOR_RED" red cubes " ANSI_COLOR_RESET, K1);
    printf("\nMove 2  : Take %d "ANSI_COLOR_GREEN" green cubes " ANSI_COLOR_RESET, K2);
    printf("\nMove 3  : Take %d "ANSI_COLOR_YELLOW" yellow cubes " ANSI_COLOR_RESET, K3);
    printf("\nInput move ([0...3]): ");
    scanf("%d", &move);
    printf("\n");
    if((move == 1) && (K1>board[0])){
    	printf("I have %d" ANSI_COLOR_RED " red cubes" ANSI_COLOR_RESET ", please try again ! \n",board[0]);
      move= -1;
    }
    if((move == 2) && (K2>board[1])){
    	printf("I have %d "ANSI_COLOR_GREEN" green cubes"ANSI_COLOR_RESET", please try again ! \n" ,board[1]);
    	move= -1;
    }
    if((move == 3) && (K3>board[2])){
    	printf("I have %d "ANSI_COLOR_YELLOW" yellow cubes"ANSI_COLOR_RESET", please try again ! \n" ,board[2]);
    	move= -1;
    }

    if (move < 0 || move > 3){
      move = -1;
    }
    if(move==0){

        printf(ANSI_COLOR_RED "\n%d " ANSI_COLOR_GREEN "%d " ANSI_COLOR_YELLOW "%d\n\n" ANSI_COLOR_RESET, board[0], board[1], board[2]);
        printf("Type 4 for "ANSI_COLOR_RED"red.\n"ANSI_COLOR_RESET);
        printf("Type 5 for "ANSI_COLOR_GREEN"green.\n"ANSI_COLOR_RESET);
        printf("Type 6 for "ANSI_COLOR_YELLOW"yellow.\n"ANSI_COLOR_RESET);
        printf("Select the color of the cube you want to take off:\n");
        scanf("%d", &move);
        printf("\n");
        if((move == 4) && (board[0]==0)){
          printf("I don't have "ANSI_COLOR_RED" red cubes "ANSI_COLOR_RESET", please try again ! \n");
          move= -1;
        }
        if((move == 5) && (board[1]==0)){
          printf("I don't have "ANSI_COLOR_GREEN" green cubes "ANSI_COLOR_RESET", please try again ! \n");
          move= -1;
        }
        if((move == 6) && (board[2]==0)){
          printf("I don't have "ANSI_COLOR_YELLOW" yellow cubes "ANSI_COLOR_RESET", please try again ! \n");
          move= -1;
        }
        if(move < 4 || move > 6){
          move = -1;
        }
    }
  }while(move == -1);

  switch(move){
      case 1:
        board[0]-=K1;
      break;
      case 2:
        board[1]-=K2;
      break;
      case 3:
        board[2]-=K3;
      break;
      case 4:
        board[0]-=1;
      break;
      case 5:
        board[1]-=1;
      break;
      case 6:
        board[2]-=1;
      break;

    }
    turn++;
}


int main(){

  int i, j;
  // computer (1) || player (-1)

  int player = 1;
  printf(ANSI_COLOR_RED "\n%d " ANSI_COLOR_GREEN "%d " ANSI_COLOR_YELLOW "%d\n\n" ANSI_COLOR_RESET, board[0], board[1], board[2]);
  while(board[0] + board[1] + board[2] != 0){
    if((turn) % 2 == 0){
      computerMove(board);
    }else {
      playerMove(board);
    }

  }
  printf(ANSI_COLOR_RED "\n%d " ANSI_COLOR_GREEN "%d " ANSI_COLOR_YELLOW "%d\n" ANSI_COLOR_RESET, board[0], board[1], board[2]);
	if(turn % 2 != 0){
    	printf("You lose.\n");
	}else{
    	printf("You win.!\n");
	}

 return 1;
}
