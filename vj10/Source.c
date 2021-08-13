#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>

#define MAX 1024

typedef struct _Stablo Stablo;
typedef struct _Stog Stog;

struct _Stablo {
	char element[MAX];
	Stablo* left;
	Stablo* right;
};

struct _Stog {
	char element[MAX];
	Stog* next;
};

int ReadFile(Stog*);
int LoadPostfix(char*, Stog*);
int Push(char*, Stog*);
Stablo* Stvori();
char* Pop(Stog*);
int ProvjeraZnaka(char);
Stablo* Proracun(Stablo*, Stog*);
int Print(Stablo*);

int main()
{
	Stog* head;
	head = (Stog*)malloc(sizeof(Stog));
	head->next = NULL;

	if (head == NULL) {
		printf("Greska u alokaciji memorije <head stog>!\n");
		return 0;
	}

	memset(head->element, '0', MAX);

	Stablo* root;
	root = Stvori();

	ReadFile(head);
	root = Proracun(root, head);

	Print(root);

	return 0;
}

int ReadFile(Stog* head)
{
	char* filename;
	filename = (char*)malloc(sizeof(char) * MAX);
	char* buffer;
	buffer = (char*)malloc(sizeof(char) * MAX);

	if (filename == NULL) {
		printf("Greska u alokaciji memorije <filename>!\n");
		return 0;
	}

	if (buffer == NULL) {
		printf("Greska u alokaciji memorije <buffer>!\n");
		return 0;
	}

	memset(buffer, '0', MAX);

	printf("Kako se zove datoteka koju zelite procitati? ");
	scanf("%s", filename);

	if (strchr(filename, '.') == NULL)
		strcat(filename, ".txt");

	FILE* fp = NULL;
	fp = fopen(filename, "r");

	if (fp == NULL) {
		printf("Greska u otvaranju datoteke!\n");
		return 0;
	}

	fgets(buffer, MAX, fp);

	LoadPostfix(buffer, head);

	return 0;
}

int LoadPostfix(char* buffer, Stog* head)
{
	int pomak = 0;
	char* znak;
	znak = (char*)malloc(sizeof(char) * MAX);

	if (znak == NULL) {
		printf("Greska u alokaciji memorije <znak>!\n");
		return 0;
	}

	memset(znak, '0', MAX);

	while (sscanf(buffer, " %s %n", znak, &pomak) == 1) {
		Push(znak, head);

		buffer += pomak;
		pomak = 0;
	}

	return 0;
}

int Push(char* znak, Stog* head)
{
	Stog* p;
	p = (Stog*)malloc(sizeof(Stog));

	if (p == NULL) {
		printf("Greska u alokaciji memorije <stog p>!\n");
		return 0;
	}

	p->next = head->next;
	head->next = p;
	strcpy(p->element, znak);

	return 0;
}

Stablo* Stvori()
{
	Stablo* novi;
	novi = (Stablo*)malloc(sizeof(Stablo));

	if (novi == NULL) {
		printf("Greska u alokaciji memorije <stablo novi>!\n");
		return NULL;
	}

	novi->left = NULL;
	novi->right = NULL;

	return novi;
}

char* Pop(Stog* head)
{
	char* pomocni;
	pomocni = (char*)malloc(sizeof(char) * MAX);

	if (pomocni == NULL) {
		printf("Greska u alokaciji memorije <pomocni>!\n");
		return NULL;
	}

	if (head->next == NULL) {
		printf("Greska, prazan stog!\n");
		return NULL;
	}

	Stog* temp;

	temp = head->next;
	strcpy(pomocni, temp->element);
	head->next = head->next->next;
	free(temp);

	return pomocni;
}

int ProvjeraZnaka(char znak)
{
	if (znak == '+')
		return 1;
	else if (znak == '-')
		return 1;
	else if (znak == '*')
		return 1;
	else if (znak == '/')
		return 1;

	else
		return 0;
}

Stablo* Proracun(Stablo* root, Stog* head)
{
	char* string;

	string = Pop(head);

	if (string == NULL) {
		printf("Greska prilikom skidanja sa stoga!\n");
		return NULL;
	}

	root = Stvori();

	strcpy(root->element, string);

	if (ProvjeraZnaka(root->element[0])) {
		root->right = Proracun(root->right, head);
		root->left = Proracun(root->left, head);
	}

	return root;
}

int Print(Stablo* root)
{

	if (root == NULL) {
		return 0;
	}

	Print(root->right);

	printf("%s", root->element);

	Print(root->left);

	return 0;
}