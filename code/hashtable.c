/*
简单的哈希表实现
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nlist {
  char *name;         /*名称*/
  char *defn;         /*替换内容*/
  struct nlist *next; /*下一个*/
};

#define HASHSIZE 1
struct nlist *hashtable[HASHSIZE];

unsigned hash(char *s) {
  unsigned hashval;
  for (hashval = 0ul; *s != '\0'; s++)
    hashval = *s + 31 * hashval;
  return hashval % HASHSIZE;
}

struct nlist *lookup(char *name) {
  struct nlist *p;
  for (p = hashtable[hash(name)]; p != NULL; p = p->next) {
    if (strcmp(name, p->name) == 0) {
      return p;
    }
  }
  return NULL;
}

struct nlist *install(char *name, char *defn) {
  struct nlist *p;
  unsigned hashval;
  // printf("installing:%s = %s\n", name, defn);

  if ((p = lookup(name)) == NULL) { /*没有定义过*/
    p = (struct nlist *)malloc(sizeof(p));
    if (p == NULL || (p->name = strdup(name)) == NULL)
      return NULL;
    hashval = hash(name);
    p->next = hashtable[hashval];
    hashtable[hashval] = p;
  } else { /*已经定义过*/
    free(p->defn);
  }

  /*无论是否定义过,都有新的定义值*/
  if ((p->defn = strdup(defn)) == NULL)
    return NULL;

  // printf("installed:%s = %s\n", name, defn);

  return p;
}

int uninstall(char *name) {
  struct nlist *np1, *np2;
  unsigned hashval = hash(name);
  for (np1 = hashtable[hashval], np2 = NULL; np1 != NULL;
       np2 = np1, np1 = np1->next) {
    if (strcmp(name, np1->name) == 0) { /*找到该名称*/
      if (np2 == NULL)                  /*此哈希值只有np1一个节点*/
        hashtable[hashval] = np1->next;
      else
        np2->next = np1->next;
      free(np1->name);
      free(np1->defn);
      free(np1);
      return 1; /*成功删除*/
    }
  }
  return 0;
}

void destory_hashtable(void) {
  struct nlist *tmp, *tmp2;
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
  struct nlist *tmp;

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

int main(int argc, char const *argv[]) {
  install("x", "1");
  install("y", "2");
  install("z", "3");
  install("m", "4");
  uninstall("x");
  uninstall("y");
  // uninstall("z");
  // uninstall("m");

  print_hashtable();
  destory_hashtable();
  return 0;
}
