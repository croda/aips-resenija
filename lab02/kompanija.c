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

struct node *head;

struct node *newNode(int ID, int plata)
{
	struct node *new = malloc(sizeof(struct node));
	new->ID = ID;
	new->plata = plata;
	new->next = NULL;
	new->prev = NULL;

	return new;
}
void append(struct node *new)
{
	struct node *current = head;
	assert(new != NULL);

	if (head == NULL) {
		head = new;
		return;
	}

	while (current != NULL) {
		if (current->ID < new->ID) {
			if (current == head) {
				head = new;
				new->next = current;
				current->prev = new;
				return;
			} else {
				new->next = current;
				new->prev = current->prev;
				current->prev->next = new;
				current->prev = new;
				return;
			}
		}

		if (current->next == NULL) break;
		current = current->next;
	}

	new->prev = current;
	current->next = new;
	new->next = NULL;
}

void delete (struct node *deleted)
{
	if (head == NULL)
		return;

	if (deleted == head) {
		head = deleted->next;
		free(deleted);
		return;
	}

	if (deleted->prev != NULL)
		deleted->prev->next = deleted->next;
	if (deleted->next != NULL)
		deleted->next->prev = deleted->prev;

	free(deleted);
}

void removePoor(int plata) // :'(
{
	struct node *p = head;

	while (p != NULL) {
		if (p->plata < plata) delete (p);
		p = p->next;
	}
}

void printList()
{
	struct node *p = head;

	while (p != NULL) {
		printf("%d %d\n", p->ID, p->plata);
		p = p->next;
	}
}

int main(void)
{
	int n, id, plata, threshold;
	scanf("%d", &n);

	head = NULL;

	for (int i = 0; i < n; i++) {
		scanf("%d", &id);
		scanf("%d", &plata);

		struct node *new = newNode(id, plata);

		append(new);
	}

	scanf("%d", &threshold);
	removePoor(threshold);
	head != NULL ? printList() : printf("nema\n");
}
