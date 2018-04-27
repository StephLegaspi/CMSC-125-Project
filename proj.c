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

	do{
		printf("[1] Easy\n");
		printf("[2] Medium\n");
		printf("[3] Hard\n");
		printf("[4] Back to menu\n");
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
	}while(choice != 4);
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

void initBoard(char board[BOARD_ROW][BOARD_COL], char *objects, int boundary){
	int i, j, x, y;

	for(i=0; i<BOARD_ROW; i++){
		for(j=0; j<BOARD_COL; j++){
			board[i][j] = ' ';
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

int main(){
	int i, j, noOfObjects, boundary;
	char board[BOARD_ROW][BOARD_COL], desc[MAX_OBJECTS][STR_LEN];
	char *objects;

	boundary = menu();
	objects = readObjects(&noOfObjects);
	initBoard(board, objects, boundary);
	printBoard(board);
	readDescriptions(desc, noOfObjects);

	for(i=0; i<noOfObjects; i++){
		printf("%s\n", desc[i]);
	}

	return 0;
}