#include <math.h>
#include <stdio.h>

// 点
struct point {
  int x;
  int y;
};

// struct rect screen;

struct point makepoint(int x, int y) {
  struct point tmp;
  tmp.x = x;
  tmp.y = y;
  return tmp;
}

struct point addpoint(struct point p1, struct point p2) {
  p1.x += p2.x;
  p1.y += p2.y;
  return p1;
}

void printpoint(struct point pt) { printf("(%d,%d)", pt.x, pt.y); }

// 矩形
struct rect {
  struct point pt1;
  struct point pt2;
};

int ptinrect(struct point p, struct rect r) {
  return p.x >= r.pt1.x && p.x < r.pt2.x && p.y >= r.pt1.y && p.y < r.pt2.y;
}

void printrect(struct rect rect) {
  printf("[");
  printpoint(rect.pt1);
  printf(" ");
  printpoint(rect.pt2);
  printf("]");
}

#define max(x, y) ((x) > (y) ? (x) : (y))
#define min(x, y) ((x) < (y) ? (x) : (y))

struct rect canonrect(struct rect r) {
  struct rect tmp;
  tmp.pt1.x = min(r.pt1.x, r.pt2.x);
  tmp.pt1.y = min(r.pt1.y, r.pt2.y);

  tmp.pt2.x = max(r.pt1.x, r.pt2.x);
  tmp.pt2.y = max(r.pt1.y, r.pt2.y);

  return tmp;
}

int main(int argc, char const *argv[]) {
  struct point pt = makepoint(3, 4);
  printpoint(pt);
  printf("\n");

  struct rect screen;
  screen.pt1 = pt;
  screen.pt2 = makepoint(0, 0);
  printrect(screen);
  printf("\n");
  printrect(canonrect(screen));
  printf("\n");

  struct point origin, *pp;
  pp = &origin;
  origin = makepoint(10, 20);
  printf("origin is (%d,%d)\n", (*pp).x, (*pp).y);

  return 0;
}

struct {
  int len;
  char *str;
} * p;
