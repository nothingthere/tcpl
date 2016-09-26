//逆波兰计算器

#define NUMBER '0' //输入内容为数字的信号

int getop(char[]);
void push(double);
double pop(void);
int getch(void);
void ungetch(int c);
