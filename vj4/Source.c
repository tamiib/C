#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<ctype.h>
#define MAX 25

struct Polinom {
	int koef;
	int pot;
	struct Polinom* next;
};
typedef struct Polinom* Poli;


int Unos(Poli);
int UnosSume(Poli, int, int);
Poli Stvori(Poli);
int Ispis(Poli);
int Suma(Poli, Poli, Poli);
int Umnozak(Poli, Poli, Poli);
int SortirajUmnozak(Poli);

int main()
{
	Poli P1, P2, S, U;

	P1 = (Poli)malloc(sizeof(struct Polinom));
	P2 = (Poli)malloc(sizeof(struct Polinom));
	S = (Poli)malloc(sizeof(struct Polinom));
	U = (Poli)malloc(sizeof(struct Polinom));

	P1->next = NULL;
	P2->next = NULL;
	S->next = NULL;
	U->next = NULL;

	Unos(P1);
	Ispis(P1);

	Unos(P2);
	Ispis(P2);

	Suma(P1, P2, S);
	printf("\nSuma polinoma:\n");
	Ispis(S);

	Umnozak(P1, P2, U);
	SortirajUmnozak(U);
	printf("\nUmnozak polinoma:\n");
	Ispis(U);

	return 0;
}

Poli Stvori(Poli head)
{
	Poli q;
	q = (Poli)malloc(sizeof(struct Polinom));

	if (head == NULL) {
		printf("\nGreska u alokaciji memorije!\n");
	}

	q->next = head->next;
	head->next = q;

	return q;
}

int Unos(Poli P)
{
	Poli q;
	Poli temp = NULL;
	q = (Poli)malloc(sizeof(struct Polinom));

	temp = P;

	char* filename;

	filename = (char*)malloc(sizeof(char) * MAX);

	printf("\nKako se zove datoteka iz koje citate polinome? ");
	scanf("%s", filename);
	if (strchr(filename, '.') == NULL)
		strcat(filename, ".txt");

	FILE* fp = NULL;
	fp = fopen(filename, "r");

	if (fp == NULL) {
		printf("Greska u otvaranju datoteke!\n");
	}


	while (!feof(fp)) {

		q = Stvori(q);

		fscanf(fp, " %d %d", &q->koef, &q->pot);

		while (temp->next != NULL && temp->next->pot > q->pot)
			temp = temp->next;
		if (temp->next != NULL && temp->next->pot == q->pot) {
			temp->next->koef += q->koef;

			if (temp->next->koef == 0) {
				q = temp->next;
				temp->next = q->next;
			}
		}
		else {
			q->next = temp->next;
			temp->next = q;
		}
	}

	fclose(fp);

	return 0;
}

int Ispis(Poli p1)
{
	p1 = p1->next;
	while (p1->next != NULL) {
		printf(" %d x^%d + ", p1->koef, p1->pot);
		p1 = p1->next;
	}
	printf(" %d x^%d ", p1->koef, p1->pot);

	printf("\n");

	return 0;
}

int UnosSume(Poli S, int k, int p)
{
	Poli q;

	while (S->next != NULL && S->next->pot > p)
		S = S->next;

	q = (Poli)malloc(sizeof(struct Polinom));
	q->koef = k;
	q->pot = p;
	q->next = S->next;
	S->next = q;

	return 0;
}


int Suma(Poli P1, Poli P2, Poli S)
{
	Poli temp = NULL;
	temp = (Poli)malloc(sizeof(struct Polinom));
	P1 = P1->next;
	P2 = P2->next;

	while (P1 != NULL && P2 != NULL) {

		if (P1->pot == P2->pot) {
			UnosSume(S, P1->koef + P2->koef, P1->pot);
			P1 = P1->next;
			P2 = P2->next;
		}

		else if (P1->pot > P2->pot) {
			UnosSume(S, P1->koef, P1->pot);
			P1 = P1->next;
		}

		else {
			UnosSume(S, P2->koef, P2->pot);
			P2 = P2->next;
		}
	}

	if (P1 != NULL)
		temp = P1;
	else
		temp = P2;

	while (temp != NULL) {
		UnosSume(S, temp->koef, temp->pot);
		temp = temp->next;
	}

	return 0;
}

int SortirajUmnozak(Poli u)
{
	Poli temp;
	temp = (Poli)malloc(sizeof(struct Polinom));

	u = u->next;
	temp = u->next;

	while (u != NULL && temp != NULL) {
		if (u->pot == temp->pot) {
			u->koef = u->koef + temp->koef;
			u->next = temp->next;
			free(temp);
			temp = u->next;
		}
		else {
			u = u->next;
			temp = temp->next;
		}
	}

	return 0;
}

int Umnozak(Poli p1, Poli p2, Poli u)
{
	Poli temp;
	p1 = p1->next;
	p2 = p2->next;
	temp = p2->next;

	while (p1 != NULL) {
		while (p2 != NULL) {
			UnosSume(u, p1->koef * p2->koef, p1->pot + p2->pot);
			p2 = p2->next;
		}
		p2 = temp;
		p1 = p1->next;
	}
	return 0;
}