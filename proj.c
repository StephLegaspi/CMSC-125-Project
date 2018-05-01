#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define BOARD_ROW 30
#define BOARD_COL 40
#define STR_LEN 64
#define MAX_OBJECTS 32
#define EASY 10
#define MEDIUM 20
#define HARD 30

int menu(){
	int choice;

	printf("[1] Easy\n");
	printf("[2] Medium\n");
	printf("[3] Hard\n");
	printf("[4] Quit\n");
	printf("Choice: ");
	scanf("%d", &choice);

	switch(choice){
		case 1:
			return EASY;
			break;
		case 2:
			return MEDIUM;
			break;
		case 3:
			return HARD;
			break;
	}
}

void readDescriptions(char desc[MAX_OBJECTS][STR_LEN], int noOfObjects){
	FILE *fptr;
	int i, r;

	fptr = fopen("descriptions.txt", "r");

	for(i=0; i<noOfObjects; i++){
		strcpy(desc[i], "+++");
	}

	for(i=0; i<noOfObjects; i++){
		srand(time(NULL));
		r = rand() % noOfObjects;

		while(strcmp(desc[r], "+++") != 0){
			r = rand() % noOfObjects;
		}
		fgets(desc[r],64,fptr);
		desc[r][strlen(desc[r])-1] = '\0';
	}
}

char *readObjects(int *noOfObjects){
	FILE *fp;
	int i;
	char c, *objs;

	fp = fopen("characters.txt", "r");
	fscanf(fp,"%d\n", noOfObjects);

	objs = (char*)malloc(sizeof(char) * (*noOfObjects));

	for(i=0; i<(*noOfObjects); i++){
		fscanf(fp,"%c\n", &c);
		objs[i] = c;
	}

	fclose(fp);
	return objs;
}

void freeObjs(char *objects, int *noOfObjects){
	int i;
	free(objects);
}

void initBoard(char board[BOARD_ROW][BOARD_COL], char *objects, int boundary){
	int i, j, x, y;

	for(i=0; i<BOARD_ROW; i++){
		for(j=0; j<BOARD_COL; j++){
			if (i==0 || j==0 || i==BOARD_ROW-1 || j==BOARD_COL-1) board[i][j] = '+';
			else board[i][j] = ' ';
		}
	}

	for(i=0; i<boundary; i++){
		srand(time(NULL));
		x = rand() % 30;
		y = rand() % 40;

		while(board[x][y] != ' '){
			x = rand() % 30;
			y = rand() % 40;
		}

		board[x][y] = objects[i];
	}
}

void printBoard(char board[BOARD_ROW][BOARD_COL]){
	int i, j;

	for(i=0; i<BOARD_ROW; i++){
		for(j=0; j<BOARD_COL; j++){
			printf("%c ", board[i][j]);
		}
		printf("\n");
	}
}

void movePlayer(char board[BOARD_ROW][BOARD_COL]){
	int i, j, x_pos, y_pos;
	char move;
	
	for(i=0; i<BOARD_ROW; i++){
		for(j=0; j<BOARD_COL; j++){
			if (board[i][j] == '#'){
				x_pos = i;
				y_pos = j;
				break;
			}
		}
	}


	do{
		scanf("%c", &move);
		printf("\n[W] Up\n");
		printf("[S] Down\n");
		printf("[A] Left\n");
		printf("[D] Right\n");
		printf("[Q] Quit\n");
		printf("Move: ");

		scanf("%c", &move);

		switch(move){
			case 'W':
				if (board[x_pos-1][y_pos] == ' '){
					board[x_pos][y_pos] = ' ';
					x_pos-=1;
					board[x_pos][y_pos] = '#';
				}
				break;
			case 'S':
				if (board[x_pos+1][y_pos] == ' '){
					board[x_pos][y_pos] = ' ';
					x_pos+=1;
					board[x_pos][y_pos] = '#';
				}
				break;
			case 'A':
				if (board[x_pos][y_pos-1] == ' '){
					board[x_pos][y_pos] = ' ';
					y_pos-=1;
					board[x_pos][y_pos] = '#';
				}
				break;
			case 'D':
				if (board[x_pos][y_pos+1] == ' '){
					board[x_pos][y_pos] = ' ';
					y_pos+=1;
					board[x_pos][y_pos] = '#';
				}
				break;
			default:
				printf("Invalid move!\n");
				break;
		}
		printf("\n");
		printBoard(board);
	}while(move!='Q');
}

int main(){
	int i, j, noOfObjects, boundary=0;
	char board[BOARD_ROW][BOARD_COL], desc[MAX_OBJECTS][STR_LEN];
	char *objects;

	while(boundary!=4){
		boundary = menu();
		objects = readObjects(&noOfObjects);
		initBoard(board, objects, boundary);
		if (boundary!=4){
			printBoard(board);
			readDescriptions(desc, noOfObjects);
			freeObjs(objects, &noOfObjects);
			movePlayer(board);
		}
	}

	

	// for(i=0; i<noOfObjects; i++){
	// 	printf("%s\n", desc[i]);
	// }

	return 0;
}