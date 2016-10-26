#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned hash(char *name) {
  unsigned hashval;
  for (hashval = 0u; *name != '\0'; name++)
    hashval = hashval + 31 * *name;
  return hashval % HASHSIZE;
}

Nlist *lookup(char *name) {
  Nlist *p;
  for (p = hashtable[hash(name)]; p != NULL; p = p->next) {
    if (strcmp(name, p->name) == 0)
      return p;
  }
  return NULL;
}

Nlist *install(char *name, char *defn) {
  Nlist *np;
  unsigned hashval;
  if ((np = lookup(name)) == NULL) {
    np = (Nlist *)malloc(sizeof(Nlist *));
    if (np == NULL || (np->name = strdup(name)) == NULL)
      return NULL;
    // np->defn = NULL;
    hashval = hash(name);
    np->next = hashtable[hashval];
    hashtable[hashval] = np;
  } else {
    free(np->defn);
  }
  if ((np->defn = strdup(defn)) == NULL)
    return NULL;
  // printf("install %s=%s\n", name, defn);
  return np;
}

int uninstall(char *name) {
  Nlist *np1, *np2;
  unsigned hashval = hash(name);
  for (np1 = hashtable[hashval], np2 = NULL; np1 != NULL;
       np2 = np1, np1 = np1->next) {
    if (strcmp(name, np1->name) == 0) {
      if (np2 == NULL)
        hashtable[hashval] = np1->next;
      else {
        np2->next = np1->next;
      }
      free(np1->name);
      free(np1->defn);
      free(np1);
      // printf("uninstall:%s\n", name);
      return 1;
    }
  }
  return 0;
}

void init_hashtable(void) {
  for (size_t i = 0; i < HASHSIZE; i++) {
    hashtable[i] = NULL;
  }
}

void destory_hashtable(void) {
  Nlist *tmp, *tmp2;

  for (size_t i = 0; i < HASHSIZE; i++) {
    tmp = hashtable[i];
    while (tmp) {
      tmp2 = tmp;
      free(tmp->name);
      free(tmp->defn);
      free(tmp);
      tmp = tmp2->next;
    }
  }
}

void print_hashtable(void) {
  Nlist *tmp;

  printf("{");

  for (size_t i = 0; i < HASHSIZE; i++) {
    tmp = hashtable[i];

    while (tmp) {
      printf("%s:%s, ", tmp->name, tmp->defn);
      tmp = tmp->next;
    }
  }

  printf("}\n");
}
//
// int main(int argc, char const *argv[]) {
//   install("x", "1");
//   install("y", "2");
//   install("z", "3");
//   install("m", "4");
//   uninstall("y");
//   uninstall("z");
//   uninstall("x");
//   uninstall("m");
//
//   print_hashtable();
//   destory_hashtable();
//   return 0;
// }
