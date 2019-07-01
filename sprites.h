#ifndef _SPRITES_H_
#define _SPRITES_H_

#include <stdint.h>

typedef struct{
	char nombre[10];
	uint16_t n;
	float cords[][2]; 
}sprite_t;

#endif
