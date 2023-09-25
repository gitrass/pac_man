#ifndef _MAP_H
#define _MAP_H
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <time.h>

#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'
#define USEPOWER 'b'

#define PLAYER '@'
#define ENEMY 'F'
#define POWER 'P'
#define GROUND '.'
#define H_WALL '-'
#define WALL '|'

int over();
void move(char direction);

struct gamemap {
    char** gamemap;
    int height;
    int lenght;
};

typedef struct gamemap MAP;

struct player{
    int x;
    int y;
};

typedef struct player POS;

void mapfree(MAP* map);
void readmap(MAP* map);
void dinalloc(MAP* map);
void copymap(MAP* destiny, MAP* origin);

int canwalk(MAP* map, char c,  int x, int y);

int findinmap(MAP* map, POS* pos, char c);
void enemy();
int enemymov(int x, int y, int* nextx, int* nexty);

int keycheck(char direction);
int barriercheck(MAP* map, int x, int y);
int limitcheck(MAP* map, int x, int y);

void movement(MAP* map, int x, int y, int nextx, int nexty);
int charactercheck(MAP* map, char character, int x, int y);
void usepower2(int nextx, int nexty, int x, int y, int qtd);
void usepower();
#endif