#include<stdio.h>
#include<stdlib.h>
#define BOARD_ROW 30
#define BOARD_COL 40

char *readFile(int *noOfObjects){
	FILE *fp;
	int i;
	char c, *objs;

	fp = fopen("characters.txt", "r");
	fscanf(fp,"%d\n", noOfObjects);

	objs = (char*)malloc(sizeof(char) * (*noOfObjects));

	for(i=0; i<(*noOfObjects); i++){
		fscanf(fp,"%c\n", &c);
		(objs[i]) = c;
	}

	fclose(fp);
	return objs;
}


int main(){
	int i, j, noOfObjects;
	char board[BOARD_ROW][BOARD_COL];
	char *objects;

	objects = readFile(&noOfObjects);

	printf("%d\n", noOfObjects);
	for(i=0; i<noOfObjects; i++){
		printf("%c", objects[i]);
	}

	return 0;
}