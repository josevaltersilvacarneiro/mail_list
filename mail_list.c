#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 100

struct mail_list {
	char name[40];
	char street[40];
	char city[30];
	char state[3];
	char zip[10];
};

typedef struct mail_list MAIL;

int  menu(void);
void init_list(MAIL *list);
void enter(MAIL *list);
void display(MAIL *list);
void save(MAIL *list);
void load(MAIL *list);

int
main(void)
{
	char choice;
	MAIL list[SIZE];

	init_list(list);

	for (;;) {
		choice = menu();

		switch (choice) {
			case 'e':
				enter(list);
				break;
			case 'd':
				display(list);
				break;
			case 's':
				save(list);
				break;
			case 'l':
				load(list);
				break;
			case 'q':
				exit(0);
		}
	}

	return 0;
}

int
menu(void)
{
	char s[80];

	do {
		printf("(E)nter\n");
		printf("(D)isplay\n");
		printf("(S)ave\n");
		printf("(L)oad\n");
		printf("(Q)uit\n");

		printf("\nYour option: ");
		scanf(" %s", s);
	} while (!strchr("edslq", tolower(*s)));

	return tolower(*s);
}

void
init_list(MAIL *list)
{
	for (register int i = 0; i < SIZE; i++)
		*list[i].name = '\0';
}

void
enter(MAIL *list)
{
	register int i;

	for (i = 0; i < SIZE; i++)
		if (!*list[i].name)
			break;

	if (i == SIZE) {
		printf("Full list\n");
		return;
	}

	printf("Name: ");
	scanf("%s", list[i].name);

	printf("Street: ");
	scanf("%s", list[i].street);

	printf("City: ");
	scanf("%s", list[i].city);

	printf("State: ");
	scanf("%s", list[i].state);

	printf("Zip Code: ");
	scanf("%s", list[i].zip);
}

void
display(MAIL *list)
{
	for (register int i = 0; i < SIZE; i++)
		if (*list[i].name) {
			printf("%s\n", list[i].name);
			printf("%s\n", list[i].street);
			printf("%s\n", list[i].city);
			printf("%s\n", list[i].state);
			printf("%s\n", list[i].zip);

			printf("\n");
		}
}

void
save(MAIL *list)
{
	FILE *fp;

	if ((fp = fopen("maillist", "wb")) == NULL) {
		printf("The file cannot be opened\n");
		return;
	}

	for (register int i = 0; i < SIZE; i++)
		if (*list[i].name)
			if (fwrite(&list[i],
						sizeof(MAIL), 1, fp) != 1)
				printf("File write error\n");

	fclose(fp);
}

void
load(MAIL *list)
{
	FILE *fp;

	if ((fp = fopen("maillist", "rb")) == NULL) {
		printf("The file cannot be opened");
		return;
	}

	init_list(list);
	
	for (register int i = 0; i < SIZE; i++)
		if (fread(&list[i],
						sizeof(MAIL), 1, fp) != 1) {
			if (feof(fp))
				break;
			printf("File read error\n");
		}

	fclose(fp);
}
