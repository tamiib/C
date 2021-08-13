#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<malloc.h>
#define MAX 1024

/* Napisati program koji iz datoteke èita postfiks izraz
i zatim korištenjem stoga raèuna rezultat.
Stog je potrebno realizirati preko vezane liste. */

struct _stog {
	float element;
	struct _stog* next;
};
typedef struct _stog Stog;
typedef struct _stog* Pozicija;

int Citaj(Pozicija);
Pozicija Push(Pozicija, float);
float Pop(Pozicija);
int Izracunaj(Pozicija, char);

int main()
{
	Pozicija head;
	head = (Pozicija)malloc(sizeof(Stog));
	head->next = NULL;

	Citaj(head);
	printf("\n%f", head->next->element);

	return 0;
}

Pozicija Push(Pozicija head, float broj)
{
	Pozicija q;
	q = (Pozicija)malloc(sizeof(Stog));

	q->next = head->next;
	head->next = q;
	q->element = broj;

	return q;
}

float Pop(Pozicija head)
{
	float broj = 0.0;
	Pozicija tmp;
	tmp = head->next;

	broj = tmp->element;
	head->next = tmp->next;
	free(tmp);

	return broj;
}

int Citaj(Pozicija head)
{
	char* filename;
	char buffer[MAX];
	char* pokbuf = buffer;
	filename = (char*)malloc(sizeof(char) * MAX);

	printf("\nKako se zove datoteka iz koje citate izraz? ");
	scanf("%s", filename);
	if (strchr(filename, '.') == NULL)
		strcat(filename, ".txt");

	FILE* fp = NULL;
	fp = fopen(filename, "r");

	if (fp == NULL) {
		printf("Greska u otvaranju datoteke!\n");
	}

	fgets(buffer, MAX, fp);

	fclose(fp);

	while (strlen(pokbuf) > 0) {
		char operacija = 0;
		float broj = 0;
		int pomak = 0;

		if (sscanf(pokbuf, " %f%n", &broj, &pomak) == 1) {
			Push(head, broj);
			pokbuf += pomak;
		}
		else {
			sscanf(pokbuf, " %c%n", &operacija, &pomak);
			Izracunaj(head, operacija);
			pokbuf += pomak;
		}
	}

	return 0;
}

int Izracunaj(Pozicija head, char operacija)
{
	float br1;
	float br2;

	switch (operacija) {
	case '+':
		br1 = Pop(head);
		br2 = Pop(head);
		Push(head, br1 + br2);
		break;

	case '-':
		br1 = Pop(head);
		br2 = Pop(head);
		Push(head, br2 - br1);
		break;

	case '*':
		br1 = Pop(head);
		br2 = Pop(head);
		Push(head, br2 * br1);
		break;

	case '/':
		br1 = Pop(head);
		br2 = Pop(head);
		if (br1 == 0)
			printf("\nDijeljenje s 0 nije dozvoljeno!");
		else
			Push(head, br2 / br1);
		break;
	}

	return 0;
}