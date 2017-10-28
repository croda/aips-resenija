#include <malloc.h>
#include <stdio.h>

struct node {
	int data;
	struct node *next;
	struct node *prev;
};

struct node *new_list()
{
	struct node *head = malloc(sizeof(struct node));
	head = NULL;

	return head;
}

void dodadi(struct node **head, int data)
{
	struct node *p = *head;
	struct node *new = malloc(sizeof(struct node));
	new->data = data;

	if (*head == NULL) {
		*head = new;
		return;
	}

	while (p != NULL) {
		if (p->next == NULL)
			break;
		p = p->next;
	}

	new->prev = p;
	p->next = new;
}

void pecati_lista(struct node **head)
{
	struct node *p = *head;

	while (p != NULL) {
		p->next != NULL ? printf("%d ", p->data)
				: printf("%d", p->data);
		p = p->next;
	}
}

int main()
{
	int i, n, info;
	struct node *lista, *lista_parni, *lista_neparni;

	lista = new_list();
	lista_parni = new_list();
	lista_neparni = new_list();

	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d", &info);
		if (info % 2 == 0)
			dodadi(&lista_parni, info);
		else
			dodadi(&lista_neparni, info);

		dodadi(&lista, info);
	}

	pecati_lista(&lista_neparni);
	printf("\n");
	pecati_lista(&lista_parni);
	return 0;
}
