#include <malloc.h>
#include <stdio.h>

#define MOVE(x)                                                                \
	moveNode(lastRef, &x);                                                 \
	lastRef = &((*lastRef)->next);

#define MOVEx2(x) MOVE(x) MOVE(x)

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

void pecatiLista(struct node *p)
{
	while (p != NULL) {
		printf("%d ", p->data);
		p = p->next;
	}
}

void moveNode(struct node **dest, struct node **src)
{
	struct node *newNode = *src;

	*src = newNode->next;
	newNode->next = *dest;
	*dest = newNode;
}

/*			 Abandon all hope   TODO: debug SIGSEGV
void dopuni(struct node ***lastRef, struct node **a, struct node **b)
{

	while (1) {
		while (1) {
			if (a == NULL) {
				*lastRef = b;
				break;
			} else {

				moveNode(*lastRef, a);
				*lastRef = &((**lastRef)->next);
			}
		}
		if (b == NULL) {
			*lastRef = a;
			break;
		} else {

			moveNode(*lastRef, b);
			*lastRef = &((**lastRef)->next);
		}
	}
} */

// gjubre ,  TODO: refactor
struct node *specialJoin(struct node *a, struct node *b)
{
	struct node *result = NULL;
	struct node **lastRef = &result;

	// dve po dve
	while (1) {
		if (a == NULL || a->next == NULL) {
			*lastRef = b;
			break;
		} else if (b == NULL || b->next == NULL) {
			*lastRef = a;
			break;
		} else {

			MOVEx2(a);
			MOVEx2(b);
		}
	}

	//	dopuni(&lastRef, &a, &b);

	while (1) {
		while (1) {
			if (a == NULL) {
				*lastRef = b;
				break;
			} else {

				MOVE(a);
			}
		}
		if (b == NULL) {
			*lastRef = a;
			break;
		} else {

			MOVE(b);
		}
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

	r = specialJoin(p1, p2);
	pecatiLista(r);

	return (0);
}
