#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX 50

/*
md - make directory
cd <dir ime> - open <dir ime>
cd.. - go back one directory
dir - list the files in current directory
izlaz
*/

typedef struct _stablo Stablo;
struct _stablo {
	char* ime;

	Stablo* child;
	Stablo* sibling;
};

typedef struct _stog Stog;
struct _stog {
	Stablo* directory;

	Stog* next;
	Stog* prev;
};

int MakeDir(Stablo*);
int Menu(Stablo*, Stog*);
int Dir(Stablo*);
Stablo* cd(Stablo*, Stog*);
Stablo* Back(Stablo*, Stog*);
Stablo* FindByName(char*, Stablo*);
int PushStog(Stog*, Stablo*);
Stablo* PopStog(Stog*);
int Linija(Stog*, Stablo*, Stablo*);
Stog* FindLast(Stog*);

int main()
{
	Stablo* root;
	root = (Stablo*)malloc(sizeof(Stablo));
	root->child = NULL;
	root->sibling = NULL;
	Stog* head;
	head = (Stog*)malloc(sizeof(Stog));
	head->next = NULL;
	head->prev = NULL;
	int status = 0;
	root->ime = (char*)malloc(MAX * sizeof(char));
	root->ime = "C:";

	do {
		status = Menu(root, head);
	} while (!status);

	return 0;
}

int Linija(Stog* head, Stablo* root, Stablo* currentFile)
{
	Stog* s;

	s = FindLast(head);

	printf("\n");
	if (head->next == NULL) {
		printf("%s>", root->ime);
		return 0;
	}

	while (s->prev != NULL) {
		printf("%s>", s->directory->ime);
		s = s->prev;
	}

	printf("%s>", currentFile->ime);

	return 0;
}

Stog* FindLast(Stog* head)
{
	Stog* s;
	s = head->next;

	if (s == NULL) {
		return NULL;
	}

	while (s->next != NULL) {
		s = s->next;
	}

	return s;
}

int Menu(Stablo* root, Stog* head) {
	Stablo* CurrentFile = root;
	char command[MAX] = { 0 };

	printf("****************************************\n");
	printf("md <filename> - Dodaj novi direktorij\n");
	printf("cd <filename> - Otvori direktorij\n");
	printf("cd.. - Zatvoriti direktorij\n");
	printf("dir - Ispisi listu direktorija u trenutnome direktoriju\n");
	printf("refresh - Ponovo ispisi izbornik\n");
	printf("exit - Izlaz\n");
	printf("****************************************\n");

	while (1) {
		//printf("%s>", CurrentFile->ime);
		Linija(head, root, CurrentFile);
		scanf("%s", command);

		if (!strcmp(command, "md")) {
			MakeDir(CurrentFile);
		}

		else if (!strcmp(command, "cd")) {
			CurrentFile = cd(CurrentFile, head);
		}

		else if (!strcmp(command, "cd..")) {
			CurrentFile = Back(CurrentFile, head);
		}

		else if (!strcmp(command, "dir")) {
			Dir(CurrentFile);
		}

		else if (!strcmp(command, "exit")) {
			return 1;
		}

		else if (!strcmp(command, "refresh")) {
			return 0;
		}

		else
			printf("Naredba nije pronadena!\n");
	}

	return 0;
}

int MakeDir(Stablo* currentFile) {
	Stablo* directory;
	directory = (Stablo*)malloc(sizeof(Stablo));
	directory->ime = (char*)malloc(MAX * sizeof(char));

	if (!directory)
		printf("Memorija nije uspjesno alocirana");

	if (currentFile->child != NULL) {
		currentFile = currentFile->child;
		while (currentFile->sibling != NULL) {
			currentFile = currentFile->sibling;
		}
		currentFile->sibling = directory;
	}

	else
		currentFile->child = directory;

	//printf("Unesite ime direktorija: ");
	scanf(" %s", directory->ime);

	directory->sibling = NULL;
	directory->child = NULL;

	return 0;
}

int Dir(Stablo* currentFile) {
	if (currentFile->child == NULL) {
		printf("Prazan direktorij!\n");
		return 0;
	}

	currentFile = currentFile->child;

	printf("DIRECTORIES: \n");
	printf("\t- %s\n", currentFile->ime);

	while (currentFile->sibling != NULL) {
		printf("\t- %s\n", currentFile->sibling->ime);
		currentFile = currentFile->sibling;
	}

	return 0;
}

Stablo* FindByName(char* name, Stablo* currentFile) {
	if (currentFile->child == NULL) {
		printf("Direktorij je prazan!");
		return 0;
	}

	currentFile = currentFile->child;

	while (strcmp(name, currentFile->ime) != 0 && currentFile->sibling != NULL) {
		currentFile = currentFile->sibling;
	}

	if (currentFile->sibling == NULL) {
		if (strcmp(name, currentFile->ime) != 0)
			return 0;
		else
			return currentFile;
	}

	else
		return currentFile;
}

int PushStog(Stog* head, Stablo* directory) {
	Stog* q = (Stog*)malloc(sizeof(Stog));

	q->next = head->next;
	q->prev = head;
	if (head->next != NULL) {
		head->next->prev = q;
	}
	head->next = q;
	q->directory = directory;

	return 0;
}

Stablo* PopStog(Stog* head) {
	Stog* q = (Stog*)malloc(sizeof(Stog));
	Stablo* p;

	if (head->next == NULL)
		return NULL;

	q = head->next;
	p = q->directory;
	head->next = head->next->next;
	if (head->next != NULL)
		head->next->prev = head;
	free(q);

	return p;
}

Stablo* Back(Stablo* currentFile, Stog* head)
{
	Stablo* SearchedFile;

	SearchedFile = PopStog(head);

	if (SearchedFile == NULL) {
		printf("Ne moze se izaci iz root direktorija!\n");
		SearchedFile = currentFile;
	}

	return SearchedFile;
}

Stablo* cd(Stablo* currentFile, Stog* head)
{
	Stablo* SearchedFile;
	char* imeDir;
	imeDir = (char*)malloc(MAX * sizeof(char));

	//printf("Koji direktorij zelite otvoriti: ");
	scanf("%s", imeDir);

	if (currentFile->child == NULL) {
		printf("Nema direktorija koji mozete otvoriti!\n");
		return currentFile;
	}

	SearchedFile = FindByName(imeDir, currentFile);
	if (SearchedFile == 0) {
		printf("Direktorij nije pronaden\n");
		return currentFile;
	}

	PushStog(head, currentFile);

	return SearchedFile;
}