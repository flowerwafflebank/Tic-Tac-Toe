#include <stdio.h>
#include <time.h>
#include <stdlib.h>


char letlist[3]={'A','B','C'};
char numlist[3]={'1','2','3'};
char space = ' ';
char b[9];
char  play1char, oppchar;
int count = 4;
int m;
char mode;
int checker; //helps skip the computer turn if your move was invalid.
int over;

void print_board(char board[])
{
  printf("\n        A        B        C     \n\n   ||=======||=======||=======||\n1  ||   %c   ||   %c   ||   %c   ||\n   ||=======||=======||=======||\n2  ||   %c   ||   %c   ||   %c   ||\n   ||=======||=======||=======||\n3  ||   %c   ||   %c   ||   %c   ||\n   ||=======||=======||=======||\n\n", board[0], board[1], board[2], board[3], board[4], board[5], board[6], board[7], board[8]);
}


int check_move_and_update_board(char board[], char move[])
{
  if(move[0]!='A'&move[0]!='B'&move[0]!='C'||move[1]!='1'&move[1]!='2'&move[1]!='3'){
    printf("Error in input. Try again.\n");
  }
  int k=0;
  checker=0;
  m=0;
  for(int i = 0; i<3; i++){
    for(int j = 0; j<3; j++){
      if(move[0]==letlist[j]&move[1]==numlist[i]){
        if(board[k]!=space){
        printf("Invalid move! Space already taken! Try again.\n");
        checker=1;
        return 1; //exit function so no move is made
        }
        if((count%2)==1&mode=='M'){
          board[k]=oppchar;
          count++;
        }
        else{
          board[k]=play1char;
          count++;
        }
      }
      k++;
    }
  }
  return 0;
}


void check_end_game(char board[])
{
  int t=0;
  for(int j=0; j<3; j++){
    if(b[0+3*j]==b[1+3*j]&b[1+3*j]==b[2+3*j]&b[0+3*j]!=space){
      if(count%2==1){
        printf("==============\n== %c's win! ==\n==============\n", play1char);
      }
      else
        printf("==============\n== %c's win! ==\n==============\n", oppchar);
      print_board(b);
      over=1;
      return;
    }
    if(b[0+j]==b[3+j]&b[3+j]==b[6+j]&b[0+j]!=space){
      if(count%2==1){
        printf("==============\n== %c's win! ==\n==============\n", play1char);
      }
      else
        printf("==============\n== %c's win! ==\n==============\n", oppchar);
      print_board(b);
      over =1;
      return;
    }
  }
  if(b[0]==b[4]&b[4]==b[8]&b[0]!=space){
    if(count%2==1){
      printf("==============\n== %c's win! ==\n==============\n", play1char);
    }
    else
      printf("==============\n== %c's win! ==\n==============\n", oppchar);
    print_board(b);
    over =1;
    return;
  }
  if(b[2]==b[4]&b[4]==b[6]&b[2]!=space){
    if(count%2==1){
      printf("==============\n== %c's win! ==\n==============\n", play1char);
    }
    else
      printf("==============\n== %c's win! ==\n==============\n", oppchar);
    print_board(b);
    over =1;
    return;
  }
  //checks for tie by looking for empty spaces
  for(int i=0; i<9; i++){
    if(b[i]==space)
      t++;
  }
  if(t==0){
    printf("=============\n== It's a TIE! ==\n=============\n");
    print_board(b);
    over =1;
    return;
  }
}


void CPU_turn(char board[])
{
  int stopper=0;
  printf("Computer's turn:\n");
  print_board(b);
  while(stopper==0){
    int rannum=rand() % 9;
    if(b[rannum]==space){
      b[rannum]=oppchar;
      count++;
      break;
    }
  }
}

void PAUSE_FUN(int delay_time_in_seconds)
{
   int milli_seconds = 1000000 * delay_time_in_seconds;
   clock_t start_time = clock();
   while (clock() < start_time + milli_seconds)
       ;
}

//--------------------------------------------------------------------------

int main()
{
  int rematch = 1;
  char next_move[2];
  char prompt_rematch;
  int end= 0;

  printf("Welcome to Tic-Tac-Toe!\nSingle Player or Multi-player? Type S or M then hit ENTER\n");
  scanf("%c", &mode);
  if(mode!='M'&mode!='S'){
    printf("Error in game mode selection...Aborting program...\n\n");
    exit(0);
  }


  while(end==0){//rematch while loop
    printf("yeet\n");
    over=0;
    for(int i=0; i<9; i++){
      b[i]=space;
    }


    //single player mode
    if(mode=='S'){
      printf("\nLaunching single player mode...\n\n");
      printf("Type X or O to select X's or O's then hit ENTER.\n");
      scanf(" %c", &play1char);
      if(play1char!='X'&play1char!='O'){
        printf("Error in character selection...Aborting program...\n");
        exit(0);
      }
      if(play1char=='X')
        oppchar='O';
      else
        oppchar='X';
      printf("Type the letter (caps) followed followed by the number of the space you want to select.\n(e.g. 'A1')\n");
      while(over==0){
        printf("Your turn!\n");
        print_board(b);
        scanf(" %s", next_move);
        printf("\n\n\n");
        check_move_and_update_board(b, next_move);
        if(checker==1)
          continue;
        check_end_game(b);
        if(over==1)
          continue;
        CPU_turn(b);
        PAUSE_FUN((rand() % 4));
        check_end_game(b);
      }
    }


    //multiplayer mode
    if(mode=='M'){
      printf("\nLaunching multi-player mode...\n\n");
      printf("Player One: Type X or O to select X's or O's then hit ENTER.\n");
      scanf(" %c", &play1char);
      if(play1char!='X'&play1char!='O'){
        printf("Error in character selection...Aborting program...\n");
        exit(0);
      }
      if(play1char=='X')
        oppchar='O';
      else
        oppchar='X';
      printf("Type the letter (caps) followed followed by the number of the space you want to select.\n(e.g. 'A1')\n");
      while(end==0){
        if(count%2==1){
          printf("%c's turn:\n", oppchar);
        }
        else{
          printf("%c's turn:\n", play1char);
        }
        print_board(b);
        scanf(" %s", next_move);
        printf("\n\n\n");
        check_move_and_update_board(b, next_move);
        check_end_game(b);
      }
    }


    //asks for a rematch
    PAUSE_FUN(3);
    printf("Would you like a rematch?\n");
    printf("Type Y or N:\n");
  //  fflush(stdin);
    scanf("%s\n", &prompt_rematch);
  //  printf("%c", prompt_rematch);
    if(prompt_rematch=='Y'){
    //  PAUSE_FUN(1);
    //  printf("%c, %d\n",mode, rematch);
    }
    else if(prompt_rematch=='N'){
      printf("Thanks for playing...\n");
      exit(0);
    }
    else{
      printf("Error in rematch selection...Aborting program...\n");
      exit(0);
    }
  }
}
