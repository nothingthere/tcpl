/*实现程序打印文档中所有单词，每个单词打印在文档中出现的行数。
排序无实意单词如"the"和"and"等。*/
#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct line {
  size_t num;        /* @num单词所在的行数*/
  size_t count;      /*该单词在此行出现的次数*/
  struct line *left; /*为使行数递增排序，使用二叉树数据结构*/
  struct line *right;
} Line;

typedef struct word {
  char *word; /*节点单词*/
  Line *line; /*行描述结构体*/
  struct word *left;
  struct word *right;
} Word;

/*内存分配*/
Line *alloc_line(void) { return (Line *)malloc(sizeof(Line)); }
Word *alloc_word(void) { return (Word *)malloc(sizeof(Word)); }

/*内存释放*/
void free_line(Line *line) {
  if (line != NULL) {
    free_line(line->left);
    free_line(line->right);
    free(line);
  }
}

void free_word(Word *word) {
  if (word != NULL) {
    free(word->word);
    free_line(word->line);
    free_word(word->left);
    free_word(word->right);
    free(word);
  }
}

// 添加节点
Line *add_line(Line *line, int line_num) {
  int cond;
  if (line == NULL) {
    line = (Line *)malloc(sizeof(Line));
    line->num = line_num;
    line->count = 1;
    line->left = line->right = NULL;

  } else if ((cond = line_num - line->num > 0)) {
    line->right = add_line(line->right, line_num);
  } else if (cond < 0) {
    line->left = add_line(line->left, line_num);
  } else {
    line->count++;
  }

  return line;
}

// 存储单词和行数
Word *add_word(Word *word, char *s, int line_num) {
  int cond;
  if (word == NULL) {
    word = (Word *)malloc(sizeof(Word));
    word->word = strdup(s);
    word->line = NULL;
    word->line = add_line(word->line, line_num);
    word->left = word->right = NULL;

  } else if ((cond = strcmp(s, word->word)) > 0) {
    word->right = add_word(word->right, s, line_num);
  } else if (cond < 0) {
    word->left = add_word(word->left, s, line_num);
  } else {
    word->line = add_line(word->line, line_num);
  }

  return word;
}

// 打印word节点
void print_line(Line *line) {
  if (line != NULL) {
    print_line(line->left);
    // if (line->count >= 2)
    printf("\t@%-10lu X %lu\n", line->num, line->count);
    print_line(line->right);
  }
}

void print_word(Word *word) {
  if (word != NULL) {
    print_word(word->left);
    printf("\n%s\n", word->word);
    print_line(word->line);
    print_word(word->right);
  }
}

#define MAXWORD 255
int getword(char *word, int lim);
size_t total_lines = 0;
size_t total_words = 0;
int main(int argc, char const *argv[]) {
  char word[MAXWORD];
  int line;
  Word *root = NULL;

  // 测试getword
  // do {
  //   while ((line = getword(word, MAXWORD)) != EOF)
  //     if (isalpha(word[0]))
  //       printf("%d %s\n", line, word);
  // } while (0);
  //
  while ((line = getword(word, MAXWORD)) != EOF) {
    if (isalpha(word[0])) {
      total_words++;
      // printf("%s\n", word);
      root = add_word(root, word, line);
    }
  }

  print_word(root);
  printf("总行数：%lu\t总单词数：%lu\n", total_lines, total_words);
  free_word(root);
  return 0;
}

#define IS_NEWLINE(c) ((c) == '\n')

int getword(char *word, int lim) {
  int getch(void);
  void ungetch(int c);
  static int line = 0;
  int c;
  while (isspace(c = getch())) {
    if (IS_NEWLINE(c)) {
      line++;
      if (line > total_lines)
        total_lines = line;
      // printf("换行\n");
    }
  }

  if (c != EOF) {
    *word++ = c;
  }

  if (!isalpha(c)) {
    *word = '\0';
    if (c == EOF)
      return EOF;
    else
      return line;
  }

  // while (--lim) {
  //   c = getch();
  //   *word++ = c;
  //   if (!isalnum(c)) {
  //     ungetch(c);
  //     break;
  //   }
  // }
  for (; --lim; word++) {
    if (!isalnum(*word = getch())) {
      ungetch(*word);
      break;
    }
  }
  *word = '\0';
  return line;
}

#define BUFFSIZE 1
char buff[BUFFSIZE];
char *buffp = buff;
int getch(void) { return buffp > buff ? *--buffp : getchar(); }

void ungetch(int c) {
  if (buffp < buff + BUFFSIZE)
    *buffp++ = c;
  else
    printf("error：buff已满\n");
}
