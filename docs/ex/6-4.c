/*实现程序打印不同单词在文档中出现的次数，按出现次数递减排序，单词前需打印次数。
*/

/*
实现步骤：
1.使用二叉树结构读取单词
2.所有节点写入数组，并记录数量
3.快速排序数组
4.打印数组
5.释放内存
*/

#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  char *word;         /*单词*/
  size_t count;       /*单词出现次数*/
  struct node *left;  /*左子树*/
  struct node *right; /*右子树*/
} Node;

void print_node(Node *node) {
  if (node != NULL) {
    print_node(node->left);
    printf("%4lu %s\n", node->count, node->word);
    print_node(node->right);
  }
}

typedef int (*node_comp)(Node *, Node *);

char *blacklist[] = {"a",     "am",  "an",    "and",   "are",  "at",
                     "from",  "he",  "here",  "i",     "in",   "is",
                     "it",    "me",  "not",   "of",    "on",   "she",
                     "that",  "the", "there", "these", "they", "this",
                     "those", "to",  "us",    "was",   "we",   "you"};
#define BLACKLIST_LEN sizeof(blacklist) / sizeof(char *)

int is_in_blacklist(char *s) {
  char *t;
  char *tmp;
  for (size_t i = 0; i < BLACKLIST_LEN; i++) {
    t = blacklist[i];
    tmp = s;
    while (tolower(*tmp++) == *t++) {
      if (*tmp == '\0')
        return 1;
    }
  }
  return 0;
}

Node *alloc_node(void);
Node *add_word(Node *p, char *word);
void read_node(Node *arr[], Node *p);
void qsort_nodes(Node *arr[], int left, int right, node_comp comp);
int comp_node(Node *node1, Node *node2);
void print_arr(Node *arr[], int num);
void free_node(Node *p);
int getword(char *word, int lim);

#define MAXWORD 255
size_t total_nodes = 0;

int main(int argc, char const *argv[]) {
  // printf("%lu\n", sizeof(size_t));
  char word[MAXWORD];
  Node *root = NULL;

  // 测试黑名单单词
  // for (size_t i = 0; i < BLACKLIST_LEN; i++) {
  //   if (is_in_blacklist("blacklist[i]"))
  //     printf("%s\n", blacklist[i]);
  // }
  // 读取
  // { /*测试getword*/
  //   while (getword(word, MAXWORD) != EOF) {
  //     if (isalpha(word[0])) {
  //       // printf("%s\n", word);
  //     }
  //   }
  // }

  while (getword(word, MAXWORD) != EOF) {
    if (isalpha(word[0]) && !is_in_blacklist(word)) {
      // printf("%s\n", word);
      root = add_word(root, word);
    }
  }

  // printf("total_nodes：%lu\n", total_nodes);
  // 写入数组
  Node *arr[total_nodes];
  // Node **arr = (Node **)malloc(sizeof(Node *) * total_nodes);
  // printf("%p\n", arr);
  // for (size_t i = 0; i < total_nodes; i++) {
  //   arr[i] = NULL;
  // }
  // printf("%lu\n", total_nodes);
  // read_node(arr, root);
  read_node(arr, root);
  // printf("%p\n", arr);

  qsort_nodes(arr, 0, total_nodes - 1, comp_node);
  // 测试读取是否成功
  // for (size_t i = 0; i < total_nodes; i++) {
  //   printf("%lu %s\n", i, arr[i]->word);
  // }
  // 排序数组
  // 打印数组
  // print_node(root);
  print_arr(arr, total_nodes);

  // printf("%p\n", arr);
  // print_arr(arr, total_nodes);

  // 释放二叉树
  free_node(root);
  // free(arr);
  return 0;
}

Node *alloc_node(void) { return (Node *)malloc(sizeof(Node)); }

Node *add_word(Node *p, char *word) {
  int cond;
  if (p == NULL) {
    p = alloc_node();
    if (p != NULL) {
      p->word = strdup(word);
      p->count = 1;
      p->left = p->right = NULL;
      total_nodes++;
    } else {
      printf("内存分配失败\n");
    }
  } else if ((cond = strcmp(word, p->word)) > 0) {
    p->right = add_word(p->right, word);
  } else if (cond < 0) {
    p->left = add_word(p->left, word);
  } else {
    p->count++;
  }
  return p;
}

void read_node(Node **arr, Node *p) {
  static Node **tmp = NULL;
  // if (tmp == NULL)
  // printf("static !!!!\n");
  if (arr)
    tmp = arr;
  if (p) {
    if (p->left)
      read_node(NULL, p->left);
    *(tmp++) = p;
    if (p->right)
      read_node(NULL, p->right);
  }
}

// void read_node(Node **DestArray, Node *Word) {
//   static Node **Write = NULL;
//
//   /* safety check */
//   // assert(NULL != Word);
//
//   /* store the starting point if this is the first call */
//   if (NULL != DestArray) {
//     Write = DestArray;
//   }
//
//   /* Now add this node and it's kids */
//   if (NULL != Word) {
//     *Write = Word;
//     ++Write;
//     if (NULL != Word->left) {
//       read_node(NULL, Word->left);
//     }
//     if (NULL != Word->right) {
//       read_node(NULL, Word->right);
//     }
//   }
// }

int comp_node(Node *node1, Node *node2) { return node1->count - node2->count; }

void qsort_nodes(Node *arr[], int left, int right, node_comp comp) {
  // printf("left=%d  right=%d\n", left, right);
  void swap(Node *[], int, int);
  int i, last;
  int mid = (left + right) / 2;
  if (left >= right)
    return;

  if (left != mid) /*当只有两个元素时，不需交换，节约两次索引搜索时间*/
    swap(arr, left, mid);

  last = left;

  for (i = left + 1; i <= right; i++) {
    if (comp(arr[i], arr[left]) < 0) {
      ++last;
      if (last != i)
        swap(arr, last, i);
    }
  }

  // printf("left=%d last=%d\n", left, last);
  if (last != left) /*last等于left时表明元素已经排序好，没有必要再交换回去*/
    swap(arr, left, last);
  qsort_nodes(arr, left, last - 1, comp);
  // printf("\n");
  qsort_nodes(arr, last + 1, right, comp);
  // swap(arr + left, )
}

void swap(Node *arr[], int i, int j) {
  // printf("swap:%d %d\n", i, j);
  Node *tmp;
  tmp = arr[i];
  arr[i] = arr[j];
  arr[j] = tmp;
}

void print_arr(Node *arr[], int num) {
  Node *tmp;
  int i;
  for (i = 0; i < total_nodes; i++) {
    tmp = arr[i];
    // if (tmp == NULL)
    //   printf("fuck%d\n", i);
    printf("%lu %s\n", tmp->count, tmp->word);
  }
  // printf("%d\n", num);
}

void free_node(Node *p) {
  if (p != NULL) {
    free(p->word);
    free_node(p->left);
    free_node(p->right);
    free(p);
  }
  // Node *tmp;
  // for (size_t i = 0; i < total_nodes; i++) {
  //   tmp=p[i];
  //   free(tmp->word);
  //   free(tmp)
  // }
}

int getword(char *word, int lim) {
  int getch(void);
  void ungetch(int c);
  int c;
  while (isblank((c = getch())))
    ;
  if (c != EOF) {
    *word++ = c;
  }
  if (!isalpha(c)) {
    *word = '\0';
    return c;
  }

  for (; --lim; word++) {
    if (!isalnum(*word = getch())) {
      ungetch(*word);
      break;
    }
  }

  *word = '\0';
  return word[0];
}

#define BUFFSIZE 1
char buff[BUFFSIZE];
char *buffp = buff;

int getch(void) { return buffp > buff ? *--buffp : getchar(); }

void ungetch(int c) {
  if (buffp < buff + BUFFSIZE)
    *buffp++ = c;
  else
    printf("buff已满\n");
}
