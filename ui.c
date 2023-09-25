#include "map.h"
#include <stdio.h>

char enemydraw[4][7] = {
    {" .-.  " },
    {"| OO| " },
    {"|   | " },
    {"'^^^' " }
};

char walldraw [4][7] = {
    {"......" },
    {"......" },
    {"......" },
    {"......" }
};

char herodraw[4][7] = {
    {" .--. "  },
    {"/ _.-'"  },
    {"\\  '-." },
    {" '--' "  }
};

char pilldraw[4][7] = {
    {"      "},
    {" .-.  "},
    {" '-'  "},
    {"      "}
};

char emptydraw[4][7] = {
    {"      "},
    {"      "},
    {"      "},
    {"      "}
};

void printsection(char draw[4][7], int section){
    printf("%s", draw[section]);
}

void printmap(MAP* map){
    for(int i = 0; i < map->height; i++){

        for(int section = 0; section < 4; section++){
            for(int j = 0; j < map->lenght; j++){
                switch(map->gamemap[i][j]){
                   case ENEMY: 
                   printsection(enemydraw, section);
                   break;
                   case PLAYER:
                   printsection(herodraw, section);
                   break;
                   case POWER:
                   printsection(pilldraw, section);
                   break;
                   case GROUND:
                   printsection(emptydraw, section);
                   break;
                   case WALL:
                   case H_WALL:
                    printsection(walldraw, section);
                    break;
                }
            } printf("\n");
        } 
    }
}