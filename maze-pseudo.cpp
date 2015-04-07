// Stefan Brandle
// Pseudo-code for the maze solver problem

#include <iostream>
#include <fstream>
// #include <cstdlibs>
#include "conio.h"
#include <ctime>
#include <unistd.h>

#define PAUSE_TIME 300000 

const char EXIT       = 'E';
const char VISITED    = '-';
const char WALL       = '#';
const char BADDIE     = '!';
const char BULLET     = '*';
const char POS_VIS    = '^';
//const int  PAUSE_TIME =  1 ;
int row;
int col;

using namespace std;
void loadMatrix(char masterMatrix[10][10]);
int getStartRow(int startRow);
int getStartCol(int statCol);
void copyMatrix(char matrix[10][10], char masterMatrix[10][10], int startRow, int startCol, char WALL);
bool solution(bool ifEscape, int startRow, int startCol, char matrix[10][10], bool ifVisit, int& ammo, int &posVisCount);
void findPosVis(int &startRow, int &startCol, char matrix[10][10]);

int main(){
     int  startCol    = 0; 
     int  startRow    = 0;
     int  ammo        = 3;
     int  posVisCount = 0;
     char masterMatrix[10][10];
     char matrix[10][10];
     bool ifEscape = false;
     bool ifVisit = false;
     
     cout << conio::clrscr();
     cout << conio::gotoxy(1,1);
     loadMatrix(masterMatrix);
     copyMatrix(matrix,masterMatrix, startRow, startCol, WALL);
     startRow = getStartRow(startRow);
     startCol = getStartCol(startCol);
     // display person
     cout << conio::gotoxy(startRow + 3, startCol + 2) << '@' << "\b";
     if (solution(ifEscape, startRow, startCol, matrix, ifVisit, ammo, posVisCount)) {
	cout << conio::gotoxy(21,1) << conio::bgColor(conio::BLACK) << "Happy day" << endl;
     } else if (ammo >=1 && posVisCount >= 1) {
     	while (ammo >= 1 && posVisCount >= 1) {
		findPosVis(startRow, startCol, matrix);
		posVisCount--;
    		if (solution(ifEscape, startRow, startCol, matrix, ifVisit, ammo, posVisCount)) {
			cout << conio::gotoxy(21,1) << conio::bgColor(conio::BLACK) << "Happy day" << endl;
		}
        }
    } else {
       cout << conio::gotoxy(21,1) << conio::bgColor(conio::BLACK) << "Less happy day.  Ammo: " << ammo << endl;
    }
     //	getStart(startCol, startRow);
     //}

     return 0;
}

bool solution(bool ifEscape, int startRow, int startCol, char matrix[10][10], bool ifVisit, int& ammo, int &posVisCount){   
    
    //sleep(PAUSE_TIME);
    //cout << conio::gotoxy(startRow + 3, startCol + 2)<< '@' << flush;    

    //These next lines deal with establishing visited-ness, NOT BASE CASE
    if (matrix[startRow][startCol] != EXIT && matrix[startRow][startCol] != WALL && matrix[startRow][startCol] != BADDIE && matrix[startRow][startCol] != BULLET&& matrix[startRow][startCol] != POS_VIS){
       if (matrix[startRow][startCol] == VISITED) {
	   ifVisit = true;
       }
       else {
	   ifVisit = false;
   	   matrix[startRow][startCol] = VISITED;
           // next two lines deal with printing character
           if (!( startRow>9||startRow<0||startCol>9||startCol<0) ){
	      usleep(PAUSE_TIME);
              for (row = 0; row < 10; row++){
                for (col = 0; col < 10; col++){
                  cout << conio::gotoxy(row + 3, col + 2) << matrix[row][col];
}
}	
              cout << conio::gotoxy(startRow + 3, startCol + 2)<< '@' << "\b" << flush;    
           }
       }   
    }
    //Base cases begin here
    //cout << startRow << startCol << endl; //INSERT THIS to view progress
    if ( startRow>9||startRow<0||startCol>9||startCol<0 ){
          //cout << "outside of maze" << endl;
	  ifEscape = false;
	  return ifEscape; //outside matrix
    }
    else if ( matrix[startRow][startCol] == BADDIE) {
          if ( ammo >= 1){
              ammo = ammo - 1;
              usleep(PAUSE_TIME);
              //cout << "Ammo down";
              matrix[startRow][startCol] = VISITED;
          }
          else{
             for (int c = -1; c<=1; c+=2){
                  if (matrix[startRow][startCol+c] == VISITED){
                     matrix[startRow][startCol+c] = POS_VIS;
		     posVisCount++;
                  }
                  if (matrix[startRow+c][startCol] == VISITED){
                     matrix[startRow+c][startCol] = POS_VIS;
		     posVisCount++;
                  }
 	     usleep(PAUSE_TIME);
             return false;
             }
          }
     }
    else if ( matrix[startRow][startCol] == '*') {
         ammo += 1;
         matrix[startRow][startCol] = VISITED;
   }
    else if ( matrix[startRow][startCol] == WALL){
          //cout << "inWall" << endl;
	  ifEscape = false;
	  return ifEscape; //on wall
    }
    else if( matrix[startRow][startCol] == EXIT){
          ifEscape = true;
	  cout << conio::gotoxy(20,1) << conio::bgColor(conio::BLACK) << "at exit ammo: " << ammo << endl;
          return ifEscape; //Escaped
    }
    //else if ( position has already been visited ) return false;
    else if(ifVisit){
	//cout << "been here" << endl;
	ifEscape = false;
	return ifEscape; //attempting to loop
    } 
   
    if( solution(ifEscape, startRow-1, startCol, matrix, ifVisit, ammo, posVisCount)){
	  ifEscape = true;
          cout << conio::gotoxy(startRow + 3, startCol + 2) << conio::bgColor(conio::GREEN) << '-' << "\b" << flush;
	  usleep(PAUSE_TIME);
          return ifEscape;
    } 
    if( solution(ifEscape, startRow+1, startCol, matrix, ifVisit, ammo, posVisCount)){ 
          ifEscape = true;
          cout << conio::gotoxy(startRow + 3, startCol + 2) << conio::bgColor(conio::GREEN) << '-' << "\b" << flush;
   	  usleep(PAUSE_TIME);
	  return ifEscape;
    }
    if( solution(ifEscape, startRow, startCol-1, matrix, ifVisit, ammo, posVisCount)){
          ifEscape = true;
          cout << conio::gotoxy(startRow + 3, startCol + 2) << conio::bgColor(conio::GREEN) << '-' << "\b" << flush;
   	  usleep(PAUSE_TIME);
	  return ifEscape;
    }
    if (solution(ifEscape, startRow, startCol+1, matrix, ifVisit, ammo, posVisCount)){ 
          ifEscape = true;
          cout << conio::gotoxy(startRow + 3, startCol + 2) << conio::bgColor(conio::GREEN) << '-' << "\b" << flush;
   	  usleep(PAUSE_TIME);
	  return ifEscape;
    }
    else{
	ifEscape = false;
        return ifEscape;
    }
    //cout << conio::clrscr();
    usleep(PAUSE_TIME);
    for (row = 0; row < 10; row++){
      for (col = 0; col < 10; col++){
        cout << conio::gotoxy(row + 3, col + 2) << matrix[row][col];
      }
    } 	
}
char newline;

void loadMatrix(char masterMatrix[10][10]){
  char fileName[100];
  cout << "enter file name: ";
  cin >> fileName;
  ifstream mazeFile(fileName);
  while (!mazeFile) {
      cout << "that is wrong, enter another file name: ";
      cin  >> fileName; 
      mazeFile.clear();
      ifstream mazeFile(fileName);
  }  
  for(int row=0; row<10; row++) {
      for(int col=0; col<10; col++) {
 	  mazeFile.get(masterMatrix[row][col]);
      }
      mazeFile.get(newline);
  }
}

int getStartRow(int startRow){
    cout << "Where should I begin?(x-pos): " << endl;
    cin  >> startRow;
    return startRow;
}

int getStartCol(int startCol){
    cout << "Where should I begin?(y-pos): " << endl;
    cin  >> startCol;
    return startCol;
}

void copyMatrix(char matrix[10][10], char masterMatrix[10][10], int startRow, int startCol, char Wall){
      cout << " 0123456789" << endl;
      for (row = 0; row < 10; row++){
	cout << row; 
	for (col = 0; col < 10; col++){
           matrix[row][col] = masterMatrix[row][col];
	  /* if (row == startRow && col == startCol && masterMatrix[row][col] != WALL && masterMatrix[row][col] != EXIT){
	      matrix[row][col] = 'I'; 
	   } */
           cout << conio::gotoxy(row + 3, col + 2) << matrix[row][col];
	}
	cout << endl;
     }
}

void findPosVis(int &startRow, int &startCol, char matrix[10][10]){
      for (row = 0; row < 10; row++){
	for (col = 0; col < 10; col++){
	  if (matrix[row][col] == POS_VIS){
	     startRow=row;
	     startCol=col;
	     return;
	  }
	}
      }
}
