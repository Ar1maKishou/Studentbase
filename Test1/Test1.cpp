#include "pch.h"
#include <stdio.h>
#include <conio.h>
#include <string.h>
#include<locale.h>

typedef struct tagITEM
{
	char Surname[20], Name[20];
	int Age;
} ITEM;

ITEM Men[20];

int Number;

void Print(void)
{
	int i;

	printf(" N  �������              ���                  �������\n");
	for (i = 0; i < Number; i++)
		printf("%2i. %-20s %-20s %3i\n", i + 1, Men[i].Surname,
			Men[i].Name, Men[i].Age);
} 

void Add(void)
{
	if (Number == 19)
	{
		fprintf(stderr, "���������� �������� ��� ���� �������\n");
		return;
	}

	printf("������� ������� > ");
	scanf("%s", Men[Number].Surname);
	printf("������� ��� > ");
	scanf("%s", Men[Number].Name);
	printf("������� ������� > ");
	scanf("%i", &Men[Number].Age);

	Number++;
} 

void Del(void)
{
	int i;

	Print();
	printf("������� ����� ���������� �������� > ");
	scanf("%i", &i);
	if (i < 1 || i > Number)
	{
		fprintf(stderr, "������� � ������� %i �� ����������\n", i);
		return;
	}

	for (i--; i < Number - 1; i++)
		Men[i] = Men[i + 1];

	Number--;
} 

void Save(void)
{
	FILE *F;
	int i;

	if ((F = fopen("task1.dat", "wt")) == NULL)
	{
		fprintf(stderr, "���������� ������� ��� ������ ���� 'task1.dta'\n");
		return;
	}

	fprintf(F, "%i\n", Number);
	for (i = 0; i < Number; i++)
		fprintf(F, "%s\n%s\n%i\n", Men[i].Surname, Men[i].Name, Men[i].Age);

	fclose(F);
}

void Load(void)
{
	FILE *F;
	int i;

	if ((F = fopen("task1.dat", "rt")) == NULL)
	{
		fprintf(stderr, "���������� ������� ��� ������ ���� 'task1.dta'\n");
		return;
	}

	fscanf(F, "%i", &Number);
	for (i = 0; i < Number; i++)
		fscanf(F, "%s%s%i", Men[i].Surname, Men[i].Name, &Men[i].Age);

	fclose(F);
} 

void Sort(void)
{
	int i, j;
	ITEM Temp;

	for (j = Number - 1; j > 0; j--)
		for (i = 0; i < j; i++)
			if (strcmp(Men[i].Surname, Men[i + 1].Surname) > 0)
			{
				Temp = Men[i];
				Men[i] = Men[i + 1];
				Men[i + 1] = Temp;
			}
} 

int Menu(void)
{
	int c = 0;

	while ((c < '0' || c > '6') && c != 27)
	{
		printf("0 : �����\n"
			"1 : �������� �������� � ���� ������\n"
			"2 : ��������� ���� ������ \n"
			"3 : ��������� ���� ������ \n"
			"4 : ������� ���� ������ \n"
			"5 : ����������� ���� ������\n"
			"6 : ������� �������� �� ���� ������ \n"
			">");
		c = _getch();
		printf("%c\n", c);
	}
	return c;
} 

void main(void)
{
	int Selection;
	setlocale(LC_ALL, "Russian");
	Number = 0;
	while ((Selection = Menu()) != '0' && Selection != 27)
		switch (Selection)
		{
		case '1':
			Add();
			break;
		case '2':
			Save();
			break;
		case '3':
			Load();
			break;
		case '4':
			Print();
			break;
		case '5':
			Sort();
			break;
		case '6':
			Del();
			break;
		}
}