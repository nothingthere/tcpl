typedef struct nlist {
  char *name;
  char *defn;
  struct nlist *next;
} Nlist;

#define HASHSIZE 101
Nlist *hashtable[HASHSIZE];

unsigned hash(char *name);
Nlist *lookup(char *name);
Nlist *install(char *name, char *defn);
void init_hashtable(void);
void destory_hashtable(void);
int uninstall(char *name);
void print_hashtable(void);
