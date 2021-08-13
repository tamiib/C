#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#define MAX 1024

struct _cvor {
	int element;
	struct _cvor* next;
};

typedef struct _cvor Cvor;
typedef struct _cvor* Pozicija;

int RandomGen();
void Push(Pozicija);
void PushPrvi(Pozicija);
Pozicija PronadiZadnji(Pozicija);
int Pop(Pozicija);
void Ispis(head);
int PopRed(Pozicija);

int main()
{
	Pozicija head_stog;
	Pozicija head_red;
	head_stog = (Pozicija)malloc(sizeof(Cvor));
	head_red = (Pozicija)malloc(sizeof(Cvor));

	head_stog->next = NULL;
	head_red->next = NULL;

	int i, stog[MAX], red[MAX], s_gen, r_gen, s_pop, r_pop;

	do {
		printf("Koliko clanova stoga zelite generirati [MAX 1024]? ");
		scanf(" %d", &s_gen);
	} while (s_gen <= 0 || s_gen > MAX);

	for (i = 0; i < s_gen; i++)
		Push(head_stog);

	Ispis(head_stog);

	do {
		printf("\nKoliko elemenata stoga zelite izbrisati? ");
		scanf(" %d", &s_pop);
	} while (s_pop<0 || s_pop>s_gen);

	for (i = 0; i < s_pop; i++)
		stog[i] = Pop(head_stog);

	Ispis(head_stog);
	printf("\n");

	do {
		printf("\nKoliko clanova reda zelite generirati[MAX 1024]? ");
		scanf(" %d", &r_gen);
	} while (r_gen <= 0 || r_gen > MAX);

	for (i = 0; i < r_gen; i++)
		Push(head_red);

	Ispis(head_red);

	do {
		printf("\nKoliko elemenata reda zelite izbrisati? ");
		scanf(" %d", &r_pop);
	} while (r_pop<0 || r_pop>r_gen);

	for (i = 0; i < r_pop; i++)
		red[i] = PopRed(head_red);

	Ispis(head_red);

	return 0;
}

int RandomGen()
{
	int broj = 0;

	broj = (rand() % 90) + 10;

	return broj;
}

Pozicija PronadiZadnji(Pozicija head)
{
	Pozicija p;
	p = head;

	while (p->next != NULL)
		p = p->next;

	return p;
}

void Push(Pozicija head)
{
	Pozicija q;
	Pozicija zadnji;
	q = (Pozicija)malloc(sizeof(Cvor));

	zadnji = PronadiZadnji(head);

	q->element = RandomGen();

	q->next = zadnji->next;
	zadnji->next = q;

}

int Pop(Pozicija head)
{
	Pozicija q, zadnji;
	int x;

	zadnji = PronadiZadnji(head);
	q = head;

	while (q->next->next != NULL)
		q = q->next;

	q->next = zadnji->next;
	x = zadnji->element;
	free(zadnji);

	return x;
}

void Ispis(Pozicija head)
{
	Pozicija q;
	q = head->next;

	while (q != NULL) {
		printf(" %d ", q->element);
		q = q->next;
	}
}

int PopRed(Pozicija head)
{
	Pozicija temp;
	int x;

	temp = head->next;
	x = temp->element;
	head->next = temp->next;
	free(temp);

	return x;
}