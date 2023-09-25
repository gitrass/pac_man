#include "map.h"
#include "ui.h"

int canwalk(MAP* map, char c, int x, int y){
    return
        limitcheck(map, x , y)&&
        barriercheck(map, x, y) &&
        !charactercheck(map, c, x, y);
}

void copymap(MAP* destiny, MAP* origin){
    destiny->height = origin->height;
    destiny->lenght = origin->lenght;

    dinalloc(destiny);

    for(int i = 0; i < origin->height; i++){
        strcpy(destiny->gamemap[i], origin->gamemap[i]);
    }
}

void readmap(MAP* map){ 
    FILE* mapfile;
    mapfile = fopen("map.txt", "r");
    fscanf(mapfile, "%d %d", &(map->height), (&map->lenght));
    if(mapfile == 0){
        printf("Error loading map!");
        exit(1);
    }

    dinalloc(map);

    for(int i = 0; i < 5; i++){
        fscanf(mapfile, "%s", map->gamemap[i]);
    }
    fclose(mapfile);
}

void dinalloc(MAP* map){
    map->gamemap = malloc(sizeof(char*) * map->height);
    for(int i = 0; i < map->height; i++){
        map->gamemap[i] = malloc(sizeof(char) * (map->lenght + 1));
    }
}

void mapfree(MAP* map){
     for(int i = 0; i < map->height; i++){
        free(map->gamemap[i]);
    } 
    free(map->gamemap);
}

int findinmap(MAP* map, POS* pos, char c){
    for(int i = 0; i < map->height; i++){
        for(int j = 0; j < map->lenght; j++){
            if(map->gamemap[i][j] == c){
                pos->x = i;
                pos->y = j;
                return 1;
            }
        }
    }
    return 0;
}

int charactercheck(MAP* map, char character, int x, int y){
    return map->gamemap[x][y] == character;
}

int keycheck (char direction){
    if (direction == UP ||
        direction == DOWN ||
        direction == RIGHT ||
        direction == LEFT) return 1;
    else return !keycheck; 
}

int limitcheck(MAP* map, int x, int y){
    if(x >= map->height) return 0; // check map barrier limits
    if(y >= map->lenght) return 0; // check map barrier limits
    else return 1;
}

int barriercheck(MAP* map, int x, int y){
        if(map->gamemap[x][y] == WALL || map->gamemap[x][y] == H_WALL){
            return 0;
        }
    return 1;
}

void movement(MAP* map, int x, int y, int nextx, int nexty){
    char character = map->gamemap[x][y];
    map->gamemap[nextx][nexty] = character;
    map->gamemap[x][y] = GROUND;
}