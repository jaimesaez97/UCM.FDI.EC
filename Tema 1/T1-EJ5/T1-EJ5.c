#include<stdio.h>
#include "T1-EJ5.asm"

extern int computo_media(short *p, char num){
	int media = 0;
	for(int i = 0; i < num; ++i)
		media += p[i];
	media = media/num;
	return media;
}
