#include <stdio.h>

const int boardSize = 3;
char board_sticks[3][3];
int playerInTurn = 8;

/*dirs
1=right
2=down
4=p1Owned
8=p2Owned
*/

void printLine(int i)
{
        int length = 2*boardSize;
        char lineUpper[2*boardSize];
        char lineLower[2*boardSize];
        int x=0;
        for(x=0; x<boardSize ; x++)
        {
           lineUpper[2*x] = '.';
           lineLower[(2*x)] = board_sticks[x][i] & 2 ? '|' : ' ';
           
           if(x== boardSize -1)
	   {
              lineUpper[(2*x)+1] = '\0';
              lineLower[(2*x)+1] = '\0';
           } 
           else
           {
              lineUpper[(2*x)+1] = board_sticks[x][i] & 1 ? '_' : ' ';
              lineLower[(2*x)+1] = board_sticks[x][i] & 4 ? '1' : board_sticks[x][i] & 8 ? '2' :  ' ';
           }
        }
        printf("%s",lineUpper);
        printf("\n");
        if(i < boardSize -1)
        {
            printf("%s",lineLower);
            printf("\n");
        }
};

void placeStick(char x, char y, char dir)
{
    if(
    (dir ==1 && x ==(boardSize -1)) ||
    (dir ==2 && y ==(boardSize -1))
    )
    {
       //TODO: handle invalid stick direction (outside board bounds)
    }
    else
    {
        board_sticks[x][y] = board_sticks[x][y] | dir;
    }
    
}

void printBoard()
{
    int i=0;
    for(i=0; i<boardSize; i++)
    {
        printLine(i); 
    }
};

void initBoardSticks()
{
int i,j;
for(i=0; i<boardSize; i++)
{
   for(j=0; j<boardSize; j++)
   {
      board_sticks[i][j]=0;
   }
}
}

char getNumericValue(char a)
{
   return a-'0';
}

char isCompleteSquare(char x, char y)
{
    return (board_sticks[x][y] & 1) && (board_sticks[x][y] & 2) && (board_sticks[x + 1][y] & 2) && (board_sticks[x][y + 1] & 1);
}

void assignCompleteSquares(char x, char y, char dir)
{
    if(dir==1)
    {
       if(y!=0 && isCompleteSquare(x, y -1))
       {
          board_sticks[x][y-1] = board_sticks[x][y-1] | playerInTurn;
       }
       if(y!=(boardSize -1) && isCompleteSquare(x, y))
       {
          board_sticks[x][y] = board_sticks[x][y] | playerInTurn;
       }
    }
    else
    {
        if(x!=0 && isCompleteSquare(x - 1, y))
       {
          board_sticks[x-1][y] = board_sticks[x-1][y] | playerInTurn;
       }
       if(x !=(boardSize -1) && isCompleteSquare(x, y))
       {
          board_sticks[x][y] = board_sticks[x][y] | playerInTurn;
       }
    }
}

int validateInputAndPlaceStick(char* input)
{
   char x = getNumericValue(input[0]);
   char y = getNumericValue(input[1]);
   char dir = getNumericValue(input[2]);
   if((x >=0 && x < boardSize) && 
      (y >=0 && y < boardSize) && 
      (dir >= 1 && dir <= 2))
   {
      int stickInPlace = board_sticks[x][y] & dir;
      if(stickInPlace != 0)
      {
         printf("%s", "There is already a stick at this location\n");
         return 0;
      }
      else
      {
         if((x==boardSize-1 && dir==1) || (y==boardSize-1 && dir==2))
         {
            printf("%s", "Invalid input: stick outside board\n");
            return 0;
         }
         {
            printf("%s", "Valid input\n");
            placeStick(x,y,dir);
            assignCompleteSquares(x,y,dir);
            return 1;
         }
      }
   }
   else
   {
      printf("%s", "Invalid input\n");
      return 0;
   }
}

int getScore(char player)
{
   int i = 0;
   int j = 0;
   int count = 0;

   for(i=0; i<boardSize - 1; i++)
   {
      for(j=0; j<boardSize - 1; j++)
      {
         if((board_sticks[i][j] & player))
         {
            count++;
         }
      }
   } 
   return count;
}

void printScores()
{
   printf("%s", "Player 1 score:");
   printf("%d", getScore(4));
   printf("\n");

   printf("%s", "Player 2 score:");
   printf("%d", getScore(8));;
   printf("\n");
}

void main()
{
    char input[3];
    initBoardSticks();
    while(getScore(12) < ((boardSize-1) * (boardSize -1)))
    {
       
       playerInTurn = playerInTurn==4 ? 8 : 4;
       if(playerInTurn==4)
       {
          printf("%s", "Player 1 to play\n");
       }
       else
       {
          printf("%s", "Player 2 to play\n");
       }
       printBoard();
    
       do
       {
         scanf("%s", &input);
       }while(!validateInputAndPlaceStick(input));
   }
   printf("%s", "Game Over\n");
   printScores();
   printBoard();
    
}








