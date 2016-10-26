
struct tnode {
  char *word;
  int count;
  struct tnode *left;
  struct tnode *right;
};

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXWORD 100 /*一个单词最大长度*/

struct tnode *addtree(struct tnode *tree, char *word);
void treeprint(struct tnode *tree);
int getword(char *word, int lim);
void tnode_free(struct tnode *);

int main(int argc, char const *argv[]) {
  char word[MAXWORD];
  struct tnode *root = NULL;
  // 读取病存储单词
  while (getword(word, MAXWORD) != EOF) {
    if (isalpha(word[0])) {
      root = addtree(root, word);
    }
  }
  // 打印单词
  treeprint(root);
  tnode_free(root);
  return 0;
}

struct tnode *addtree(struct tnode *tree, char *word) {
  struct tnode *talloc(void);
  char *str_dup(char *s);

  int cond;
  if (tree == NULL) {
    tree = talloc();
    tree->word = str_dup(word);
    tree->count = 1;
    tree->left = tree->right = NULL;

  } else if ((cond = strcmp(tree->word, word)) == 0) {
    tree->count++;
  } else if (cond < 0) {
    tree->right = addtree(tree->right, word);
  } else {
    tree->left = addtree(tree->left, word);
  }
  return tree;
}

void tnode_free(struct tnode *tree) {
  if (tree) {
    tnode_free(tree->left);
    tnode_free(tree->right);
    free(tree->word);
    free(tree);
  }
}
struct tnode *talloc(void) {
  return (struct tnode *)malloc(sizeof(struct tnode));
}

char *str_dup(char *s) {
  char *p = (char *)malloc(strlen(s) + 1);
  strcpy(p, s);
  return p;
}

void treeprint(struct tnode *tree) {
  if (tree != NULL) {
    treeprint(tree->left);
    printf("%4d %s\n", tree->count, tree->word);
    treeprint(tree->right);
  }
}

int getword(char *word, int lim) {
  int getch(void);
  void ungetch(int);
  int c;
  // 跳过空白字符
  while (isblank(c = getch()))
    ;

  if (c != EOF) {
    *word++ = c;
  }
  // 如果第一个字符不在单词范围内，直接返回字符（包含EOF），且完整补全单词
  if (!isalpha(c)) {
    *word = '\0';
    return c;
  }
  // 开始读取单词
  for (; --lim; word++) {
    if (!isalnum(*word = getch())) {
      ungetch(*word);
      break;
    }
  }
  *word = '\0';
  return word[0];
}

#define BUFFSIZE 2
char buff[BUFFSIZE];
char *buffp = buff;

int getch(void) { return buffp > buff ? *--buffp : getchar(); }
void ungetch(int c) {
  if (buffp < buff + BUFFSIZE) {
    *buffp++ = c;
  } else {
    printf("buff已满\n");
  }
}
