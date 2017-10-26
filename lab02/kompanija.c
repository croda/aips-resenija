//Податоците за плати на вработените во една компанија привремено се чуваат во
//двострано поврзана листа. Во секој јазол од листата се чува единствен ID на
//вработениот и неговата плата. Потребно е да се отстранат сите вработени со
//помали плати од даден износ, а остатокот да се прикажат во опаѓачки редослед
//во однос на ID-то.
//
//Во првиот ред од влезот е даден бројот на вработени, потоа наизменично се
//дадени ID-та и платата за секој од вработените и во последниот ред е износот
//во однос на кој ќе се отстрануваат вработените. На излез се печати листа (ID,
//плата) во опаѓачки редослед според ID-то на секој од вработените.
//
//Доколку нема вработени со плата поголема од дадената да се испечати: nema

#include <assert.h>
#include <malloc.h>
#include <stdio.h>

struct node {
	int ID;
	int plata;
	struct node *prev;
	struct node *next;
};

struct node *new_list(void)
{
	struct node *n = malloc(sizeof(struct node));
	n->prev = n;
	n->next = NULL;
	return n;
}

void append(struct node *current, int ID, int plata)
{
	struct node *new = malloc(sizeof(struct node));
	new->ID = ID;
	new->plata = plata;

	while (current->next != NULL) {
		current = current->next;
	}

	new->next = NULL;
	new->prev = current;
	current->next = new;
}

void delete (struct node *deleted)
{
	deleted->prev->next = deleted->next;
	deleted->next->prev = deleted->prev;
	free(deleted);
}

void deleteLess(struct node *list, int plata)
{
	struct node *p = list;

	while (p->next != NULL) {
		if (p->plata < plata) {
			delete (p);
		}

		p = p->next;
	}
}

void printList(struct node *list)
{
	while (list != NULL) {
		printf("%d %d \n", list->ID, list->plata);
		list = list->next;
	}
}

int main(void)
{
	int n, id, plata, threshold;
	scanf("%d", &n);

	struct node *list = new_list();

	for (int i = 0; i < n; i++) {
		scanf("%d", &id);
		scanf("%d", &plata);

		append(list, id, plata);
		// insert_node(id, plata);
	}

	scanf("%d", &threshold);
	deleteLess(list, threshold);
	printList(list);
}
