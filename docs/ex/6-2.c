/*实现读取C源文件程序，按字母顺序输出每组前6个字母相同的变量名。
字符串和注释内的单词不考虑。将6作为命令行参数*/

/*
变量名：除去关键字，函数名的单词，单词前可能有*作为指针变量
比较前n个字符：使用strncmp函数
数据结构：
  节点
    组节点： 字符串数组
*/

/*
读取步骤：
  读取单词
  查找树上节点中是否与单词的前n个字符相同
    如果无，创建节点
    如果等于，在节点中的树中插入单词
    如果大于，在右树上插入
    否则，左树上插入

打印：
  先打印左子树节点
  打印当前节点
    做树状打印
  打印右子树节点

C源文件变量：
  除去关键字
  除去注释
  除去字符串常量
  除去宏定义：只考虑单行宏定义

  的“单词”：可能最前面有“※”，表示指针变量


*/

typedef struct wnode {
  char *word;
  int count;
  struct wnode *prev;
  struct wnode *next;
} Wnode;

typedef struct tnode {
  Wnode *words;
  struct tnode *left;
  struct tnode *right;
} Tnode;

char *keywords[] = {"EOF",    "NULL",     "auto",    "break",  "case char",
                    "const",  "continue", "default", "do",     "double",
                    "else",   "enum",     "extern",  "float",  "for",
                    "goto",   "if　　",   "int",     "long",   "register",
                    "return", "short",    "signed",  "sizeof", "static",
                    "struct", "switch",   "typedef", "union",  "unsigned",
                    "void",   "volatile", "while"};

int keywords_len = sizeof(keywords) / sizeof(keywords[0]);

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXWORD 100 /*单词最大长度*/

Tnode *tnode_add(Tnode *tree, char *word, int n);
void tnode_free(Tnode *tree);
void tnode_print(Tnode *tree);
int getword(char *word, int lim);
int getword2(char *word, int lim);
int is_keyword(char *w);

int main(int argc, char const *argv[]) {
  // printf("%d\n", keywords_len);
  // // 测试is_keyword函数
  // do {
  //   int count = 0;
  //   for (int i = 0; i < keywords_len; i++) {
  //     // printf("%s\n", keywords[i]);
  //     if (is_keyword(keywords[i]) > -1)
  //       count++;
  //   }
  //   if (count == keywords_len)
  //     printf("is_keyword函数测试成功\n");
  //   else
  //     printf("is_keyword函数测试失败\n");
  //   // is_keyword("aut");
  // } while (0);

  //
  int n = 2; /*比较字符长度默认值，更具命令行参数更改*/
  int m;
  char word[MAXWORD];
  int c;
  Tnode *root;

  // 确定参数
  if (argc >= 3 && strncmp(argv[1], "-n", 2) == 0) {
    if ((m = atoi(argv[2])) > 0) {
      n = m;
    }
  }
  // 读取
  root = NULL;

  // 测试getword2使用测试文件test_keywords.txt
  // do {
  //   while (getword2(word, MAXWORD) != EOF)
  //     printf("%s\n", word);
  //
  // } while (0);

  while (getword2(word, MAXWORD) != EOF) {
    // printf("n=%d\n", n);
    if ((isalpha(c = word[0]) || c == '_') && is_keyword(word) < 0)
      // printf("%s\n", word);
      root = tnode_add(root, word, n);
  }
  // 打印
  tnode_print(root);
  // 释放
  tnode_free(root);
  return 0;
}

Tnode *tnode_add(Tnode *tree, char *word, int n) {
  // printf("in tnode_add: n=%d\n", n);
  int cond;
  Tnode *talloc(void);
  Wnode *wnode_add(Wnode *, char *word);
  if (tree == NULL) {
    // printf("1\n");
    tree = talloc();
    tree->words = wnode_add(tree->words, word);
    tree->left = tree->right = NULL;
  } else if ((cond = strncmp(word, tree->words->word, n)) == 0) {
    // printf("2\n");
    // printf("%s\n", word);
    tree->words = wnode_add(tree->words, word);
  } else if (cond < 0) {
    // printf("3\n");
    tree->left = tnode_add(tree->left, word, n);

  } else {
    // printf("4\n");
    tree->right = tnode_add(tree->right, word, n);
  }
  return tree;
}

Tnode *talloc(void) { return (Tnode *)malloc(sizeof(Tnode)); }
Wnode *wnode_add(Wnode *wtree, char *word) {
  int cond;
  Wnode *walloc(void);
  char *str_dup(char *);
  if (wtree == NULL) {
    wtree = walloc();
    wtree->count = 1;
    wtree->word = str_dup(word);
    wtree->prev = wtree->next = NULL;
  } else if ((cond = strcmp(word, wtree->word)) == 0) {
    wtree->count++;
    /*??????*/
  } else if (cond < 0) {
    wtree->prev = wnode_add(wtree->prev, word);
  } else {
    wtree->next = wnode_add(wtree->next, word);
  }
  return wtree;
}

Wnode *walloc(void) { return (Wnode *)malloc(sizeof(Wnode)); }
char *str_dup(char *s) {
  char *p = (char *)malloc(strlen(s) + 1);
  if (p != NULL)
    strcpy(p, s);
  return p;
}

void tnode_free(Tnode *tree) {
  void wnode_free(Wnode *);
  if (tree != NULL) {
    tnode_free(tree->left);
    tnode_free(tree->right);
    // free(tree->words->word);
    // free(tree->words);
    wnode_free(tree->words);
    free(tree);
  }
}

void wnode_free(Wnode *wtree) {
  if (wtree != NULL) {
    wnode_free(wtree->prev);
    wnode_free(wtree->next);
    free(wtree->word);
    free(wtree);
  }
}

void tnode_print(Tnode *tree) {
  void wnode_print(Wnode *);
  if (tree) {
    tnode_print(tree->left);
    wnode_print(tree->words);
    printf("\n");
    tnode_print(tree->right);
  }
}

void wnode_print(Wnode *words) {
  if (words) {
    wnode_print(words->prev);
    printf("%-4d %s\n", words->count, words->word);
    wnode_print(words->next);
  }
}

int is_keyword(char *w) {
  // printf("word=%s\n", w);
  int low = 0;
  int high = keywords_len - 1;
  int mid;
  int cond;
  while (low <= high) {
    // printf("low=%d high=%d\n", low, high);
    mid = (low + high) / 2;
    if ((cond = strcmp(w, keywords[mid])) < 0) {
      high = mid - 1;
    } else if (cond > 0) {
      low = mid + 1;
    } else {
      return mid;
    }
  }
  return -1;
}

// 获取C源文件变量
#define SHARP '#'
#define DQOUTE '"'
#define SQOUTE '\''
#define SLASH '/'
#define ARSTERISK '*'
#define UNDERSCOR '_'

#define REGETWORD                                                              \
  {                                                                            \
    *--word = '\0';                                                            \
    return getword2(word, lim);                                                \
  }

#define z 1

int getword2(char *word, int lim) {
  int c;
  // static int prev = EOF;
  int getch(void);
  void ungetch(int);

  // 跳过空白字符
  while (isspace(c = getch()))
    ;
  // 读取第一个字符
  if (c != EOF) {
    *word++ = c;
  }

  // 如果第一个字符不为合法字符，返回只字符
  if (!(isalpha(c) || (c == SHARP) || (c == DQOUTE) || (c == SQOUTE) ||
        (c == SLASH) || (c == ARSTERISK) || (c == UNDERSCOR))) {
    *word = '\0';
    return c;
  }
  switch (c) {
  case SHARP: /*跳过所有单行宏定义*/
    // printf("宏定义\n");
    while (getch() != '\n')
      ;
    REGETWORD;
    break;
  case ARSTERISK: /*指针变量*/
    REGETWORD;
    break;
  case SQOUTE:
    while ((c = getch()) != SQOUTE && c != '\\')
      ;
    if (c == '\\') {
      getch(); /*吞掉第一个转义字符可能是单引号本身的情况*/
      while ((c = getch()) != SQOUTE)
        ;
    }
    // printf("%d\n", c == SQOUTE);
    REGETWORD;
    break;
  case DQOUTE:
    while (getch() != DQOUTE)
      ;
    REGETWORD;
    break;
  case SLASH:
    c = getch();
    if (c == ARSTERISK) { /*多行注释*/
      while (getch() != ARSTERISK)
        ;
      c = getch();
      if (c != SLASH) {
        ungetch(SLASH);
        ungetch(ARSTERISK);
      }
    } else if (c == SLASH) { /*单行注释*/
      while (getch() != '\n')
        ;
    } else { /*非注释，可能为除号*/
    }
    REGETWORD;
    break;
  default: /*第一个字符为字母或下划线*/
    for (; --lim; word++) {
      if (!(isalnum(*word = getch()) || *word == UNDERSCOR)) {
        ungetch(*word);
        break;
      }
    }
    break;
  }

  *word = '\0';
  return word[0];
}

// 获取任意单词
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
  if (buffp < buff + BUFFSIZE)
    *buffp++ = c;
  else
    printf("buff已满\n");
}
