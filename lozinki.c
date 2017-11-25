#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <malloc.h>

typedef struct dict *Dict;

Dict DictCreate(void);
void DictDestroy(Dict);
void DictInsert(Dict, const char *key, const char *value);
const char *DictSearch(Dict, const char *key);
void DictDelete(Dict, const char *key);

struct elt {
    struct elt *next;
    char *key;
    char *value;
};

struct dict {
    int size;	// size of pointer table
    int n;		// num of elems stored
    struct elt **table;
};

#define INITIAL_SIZE (204)
#define GROWTH_FACTOR (2)
#define MAX_LOAD_FACTOR (1)

Dict
internalDictCreate(int size) {
    Dict d;
    int i;

    d = malloc(sizeof(*d));
    assert(d != 0);

    d->size = size;
    d->n = 0;
    d->table = malloc(sizeof(struct elt *) * d->size);
    assert(d->table != 0);

    for (i = 0; i < d->size; i++)
        d->table[i] = 0;

    return d;
}

Dict
DictCreate(void) {
    return internalDictCreate(INITIAL_SIZE);
}

void
DictDestroy(Dict d) {
    int i;
    struct elt *e;
    struct elt *next;

    for (i = 0; i < d->size; i++) {
        for (e = d->table[i]; e != 0; e = next) {
            next = e->next;

            free(e->key);
            free(e->value);
            free(e);
        }
    }

    free(d->table);
    free(d);
}

#define MULTIPLIER (97)

static unsigned long
hash_func(const char *s) {
    unsigned const char *us;
    unsigned long h;

    h = 0;

    for (us = (unsigned const char *) s; *us; us++) {
        h = h * MULTIPLIER + *us;
    }

    return h;
}

static void
grow(Dict d) {
    Dict d2;
    struct dict swap; // tmp struct for swapping ptrs later
    int i;
    struct elt *e;

    d2 = internalDictCreate(d->size * GROWTH_FACTOR);

    for (i = 0; i < d->size; i++) {
        for (e = d->table[i]; e != 0; e = e->next) {
            DictInsert(d2, e->key, e->value);
        }
    }

    // god have mercy
    swap = *d;
    *d = *d2;
    *d2 = swap;

    DictDestroy(d2);
}

void
DictInsert(Dict d, const char *key, const char *value) {
    struct elt *e;
    unsigned long h;

    assert(key);
    assert(value);

    e = malloc(sizeof(*e));
    assert(e);

    e->key = strdup(key);
    e->value = strdup(value);

    h = hash_func(key) % d->size;

    e->next = d->table[h];
    d->table[h] = e;

    d->n++;

    if(d->n > d->size * MAX_LOAD_FACTOR) {
        grow(d);
    }
}

const char *
DictSearch(Dict d, const char *key) {
    struct elt *e;

    for (e = d->table[hash_func(key) % d->size]; e != 0; e = e->next) {
        if (!strcmp(e->key, key)) { // equal
            return e->value;
        }
    }

    return 0;
}

void
DictDelete(Dict d, const char *key) {
    struct  elt **prev;
    struct elt *e;

    for (prev = &(d->table[hash_func(key) % d->size]);
            *prev != 0;
            prev = &((*prev)->next)) {
        if (!strcmp((*prev)->key, key)) {
            e = *prev;
            *prev = e->next;

            free(e->key);
            free(e->value);
            free(e);

            return;
        }
    }
}

#define MAX 20
#define forever() for(i = 0;; i++)

int
main() {
    int N,i;
    scanf("%d",&N);

    Dict mapa = DictCreate();

    char user[N][MAX];
    char pass[N][MAX];

    for(i=0; i<N; i++) {
        scanf("%s",user[i]);
        scanf("%s",pass[i]);
        DictInsert(mapa, user[i], pass[i]);
    }

    char userT[N][MAX];
    forever() {
        scanf("%s", userT[i]);
        if (!strcmp(userT[i], "KRAJ")) {
            DictDestroy(mapa);
            return 0;
        }
        scanf("%s", pass[i]);
        
        if (DictSearch(mapa, userT[i]) == 0) {
            printf("Nenajaven\n");
            continue;
        }
        if (!strcmp(DictSearch(mapa, userT[i]), pass[i])) {
            printf("Najaven");
            break;
        }
       printf("Nenajaven\n");
    }

    DictDestroy(mapa);
    return 0;
}
