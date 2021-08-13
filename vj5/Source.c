#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<ctype.h>
#define MAX 25

struct _Lista;
typedef struct _Lista Lista;

struct _Lista {
	int el;
	struct _Lista* next;
};

int CitajIzDat(Lista*);
int Ispis(Lista*);
Lista* PronadiZadnji(Lista*);
int Presjek(Lista*, Lista*, Lista*);
int Unija(Lista*, Lista*, Lista*);

int main()
{
	Lista* L1 = NULL;
	Lista* L2 = NULL;
	Lista* U = NULL;
	Lista* P = NULL;

	L1 = (Lista*)malloc(sizeof(Lista));
	L2 = (Lista*)malloc(sizeof(Lista));
	U = (Lista*)malloc(sizeof(Lista));
	P = (Lista*)malloc(sizeof(Lista));


	L1->next = NULL;
	L2->next = NULL;
	U->next = NULL;
	P->next = NULL;

	CitajIzDat(L1);
	Ispis(L1);
	CitajIzDat(L2);
	Ispis(L2);
	Presjek(L1, L2, P);
	printf("\nPresjek listi je\n");
	Ispis(P);
	Unija(L1, L2, U);
	printf("\nUnija listi je\n");
	Ispis(U);

	return 0;
}

Lista* PronadiZadnji(Lista* head)
{
	Lista* p;
	p = head;

	while (p != NULL && p->next != NULL)
		p = p->next;

	return p;
}

Lista* Stvori(Lista* head)
{
	Lista* q;
	Lista* p;
	q = (Lista*)malloc(sizeof(Lista));

	p = PronadiZadnji(head);

	q->next = p->next;
	p->next = q;

	return q;
}

int CitajIzDat(Lista* head)
{
	Lista* q = NULL;
	FILE* fp = NULL;
	char* filename;

	filename = (char*)malloc(sizeof(char) * MAX);

	printf("\nKako se zove datoteka iz koje citate polinome? ");
	scanf("%s", filename);
	if (strchr(filename, '.') == NULL)
		strcat(filename, ".txt");

	fp = fopen(filename, "r");

	if (fp == NULL) {
		printf("Greska u otvaranju datoteke!\n");
		return -1;
	}

	while (!feof(fp)) {
		q = Stvori(head);
		fscanf(fp, " %d", &q->el);
	}

	fclose(fp);

	return 0;
}

int Ispis(Lista* head)
{
	Lista* q;
	q = head->next;

	while (q != NULL) {
		printf(" %d ", q->el);
		q = q->next;
	}

	return 0;
}

int Presjek(Lista* L1, Lista* L2, Lista* P)
{
	Lista* pr;
	pr = (Lista*)malloc(sizeof(Lista));

	L1 = L1->next;
	L2 = L2->next;

	while (L1 != NULL && L2 != NULL) {
		if (L1->el > L2->el)
			L2 = L2->next;
		else if (L1->el < L2->el)
			L1 = L1->next;
		else {
			pr = Stvori(P);
			pr->el = L1->el;

			L1 = L1->next;
			L2 = L2->next;
		}

	}

	return 0;
}

int Unija(Lista* L1, Lista* L2, Lista* U)
{
	L1 = L1->next;
	L2 = L2->next;

	while (L1 != NULL && L2 != NULL) {
		if (L1->el > L2->el) {
			U = Stvori(U);
			U->el = L2->el;
			L2 = L2->next;
		}
		else if (L1->el < L2->el) {
			U = Stvori(U);
			U->el = L1->el;
			L1 = L1->next;
		}
		else {
			U = Stvori(U);
			U->el = L1->el;
			L1 = L1->next;
			L2 = L2->next;
		}
	}
	if (L1 == NULL) {
		while (L2 != NULL) {
			U = Stvori(U);
			U->el = L2->el;
			L2 = L2->next;
		}
	}
	if (L2 == NULL) {
		while (L1 != NULL) {
			U = Stvori(U);
			U->el = L1->el;
			L1 = L1->next;
		}
	}


	return 0;
}