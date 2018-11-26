#include <stdio.h>
#define R 32
#define defaultseed 1

int r[R];
int randomcnt;

void init(int seed){
	int i;
	r[0] = seed;
	for (i=1; i<31; i++) {
		r[i] = (16807LL * r[i-1]) % 2147483647;
		if (r[i] < 0) {
			r[i] += 2147483647;
		}
	}
	for (i=31; i<34; i++) {
		r[i%R] = r[(i+R-31)%R];
	}
	for (i=34; i<344; i++) {
		r[i%R] = r[(i+R-31)%R] + r[(i+R-3)%R];
	}
	randomcnt = i%R;
}

unsigned int random(){
	r[randomcnt%R] =  r[(randomcnt+R-31)%R] + r[(randomcnt+R-3)%R];
	return ((unsigned int)r[randomcnt++ %R]) >> 1; 
}

int main() {
  int i;
  init(defaultseed);

  for (i=0; i<30; i++) {
    printf("%d\n", random());
  }
}
