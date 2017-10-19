#include <malloc.h>
#include <stdio.h>

struct node {
	int data;
	struct node *next;
};

struct node *mk_link_list(int len)
{
	struct node *p = NULL;
	struct node *q = NULL;

	while (len--) {
		p = malloc(sizeof(struct node));
		p->next = q;
		q = p;
	}

	while (q != NULL) {
		scanf("%d", &q->data);
		q = q->next;
	}

	return p;
}

void mvNode(struct node **dest, struct node **src)
{
	struct node *newNode = *src;

	*src = newNode->next;
	newNode->next = *dest;
	*dest = newNode;
}

void removeDuplicate(struct node *head)
{
	struct node *current = head;

	if (current == NULL) return;

	while (current->next != NULL) {
		if (current->data == current->next->data) {
			struct node *nextNext = current->next->next;
			free(current->next);
			current->next = nextNext;
		} else {
			current = current->next;
		}
	}
}

struct node *join_lists(struct node *l1, struct node *l2)
{
	struct node *result = NULL;
	struct node **prevPtr = &result;
	while (1) {
		if (l1 == NULL) {
			*prevPtr = l2;
			break;
		} else if (l2 == NULL) {
			*prevPtr = l1;
			break;
		}

		if (l1->data <= l2->data) {
			mvNode(prevPtr, &l1);
		} else {
			mvNode(prevPtr, &l2);
		}

		prevPtr = &((*prevPtr)->next);
	}

	return result;
}

int main()
{
	struct node *p1, *p2, *r;
	int m, n;

	scanf("%d", &m);
	p1 = mk_link_list(m);

	scanf("%d", &n);
	p2 = mk_link_list(n);

	r = join_lists(p1, p2);
	removeDuplicate(r);

	while (r->next != NULL) {
		printf("%d ", r->data);
		r = r->next;
	}
	printf("%d\n", r->data);

	return (0);
}
