#include <stdio.h>
#define R 31
#define defaultseed 1

unsigned r[R];
unsigned randomcnt;

unsigned f(unsigned a){
	return a % R;
}

void init(unsigned seed){
	unsigned i;
	r[0] = seed;
	for (i=1; i<31; i++) {
		r[f(i)] = (16807LL * r[f(i-1)]) % 2147483647;
	}
	r[f(31)] = seed;
	for (i=32; i<34; i++) {
		r[f(i)] = (16807LL * r[f(i-1)]) % 2147483647;
	}
	for (i=34; i<344; i++) {
		r[f(i)] += r[f(i-3)];
	}
	randomcnt = i;
}

unsigned int random(){
	r[f(randomcnt)] += r[f(randomcnt-3)];
	return ((unsigned int)r[f(randomcnt++)]) >> 1; 
}

unsigned int randomprev(){
	if (randomcnt <= 344) 
		return 0xffffffff;
	unsigned tmp = r[f(--randomcnt)];
	r[f(randomcnt)] -= r[f(randomcnt-3)];
	return ((unsigned int)tmp) >> 1; 
}

int main() {
  int i;
  init(defaultseed);

  for (i=0; i<60; i++) {
    printf("%d\n", random());
  }

  printf("---\n");

  for (i=0; i<61; i++) {
    printf("%d\n", randomprev());
  }

  return 0;
}
