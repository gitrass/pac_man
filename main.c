#include "map.h"
#include "ui.h"

MAP map;
POS pos;

int haspower = 0;

int enemymov(int x, int y, int* nextx, int* nexty){
    int options[4][2] = {
        {x, y+1},
        {x+1, y},
        {x, y-1},
        {x-1, y}
    };

    srand(time(0));
    for(int i = 0; i < 5; i++){
        int position = rand() % 4;
        if(canwalk(&map, ENEMY, options[position][0], options[position][1])) {
            *nextx = options[position][0];
            *nexty = options[position][1];
            return 1;
        }
    }
    return 0;
}

void enemy(){
    MAP copy;

    copymap(&copy, &map);

    for(int i = 0; i < map.height; i++){
        for(int j = 0; j < map.lenght; j++){

            if(copy.gamemap[i][j] == ENEMY){

                int nextx;
                int nexty;

                int found = enemymov(i, j, &nextx, &nexty);

                if(found){
                    movement(&map, i, j, nextx, nexty);
                }
            }
        }
    }
    mapfree(&copy);
}

void usepower(){

    if(!haspower) return;

    usepower2(0, 1, pos.x, pos.y, 3);
    usepower2(0, -1, pos.x, pos.y, 3);
    usepower2(1, 0, pos.x, pos.y, 3);
    usepower2(-1, 0, pos.x, pos.y, 3);    

    haspower = 0;
}

void usepower2(int nextx, int nexty, int x, int y, int qtd){
    if(qtd == 0) return;

    int newx = x + nextx;
    int newy = y + nexty;

    if(!barriercheck(&map, newx, newy)) return;
    if(!limitcheck(&map, newx, newy)) return;

    map.gamemap[newx][newy] = GROUND;
    usepower2(nextx, nexty, newx, newy, qtd - 1);
}

int main(){
   readmap(&map);
   findinmap(&map, &pos, PLAYER);

   do{
    printf("Power: %s\n", (haspower ? "ON":"OFF"));
    printmap(&map);
    char command;
    scanf(" %c", &command);
    move(command);
    if(command == USEPOWER) usepower();

   }while(!over());

   mapfree(&map);
}

int over(){
    POS pos;

    int playerinmap = findinmap(&map, &pos, PLAYER);

    return !playerinmap;
}

void move(char direction){
    keycheck(direction);

    int nextx = pos.x;
    int nexty = pos.y;

    switch(direction) {
        case UP:
            nextx--;
            break;
        case DOWN:
            nextx++;
            break;
        case LEFT:
            nexty--;
            break;
        case RIGHT:
            nexty++;
            break;
    }
    enemy(); 
    if(!canwalk(&map, PLAYER, nextx, nexty)) return;
    
    if(charactercheck(&map, POWER, nextx, nexty)){
        haspower = 1;
    }

    movement(&map, pos.x, pos.y, nextx, nexty);
    pos.x = nextx;
    pos.y = nexty;
}
