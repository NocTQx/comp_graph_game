#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>

String file = "/home/love/CLionProjects/untitled/";

const unsigned int DIM1 = 78;
const unsigned int DIM2 = 132;

char TileMap[DIM1][DIM2];

void map_load() {

    std::ifstream fs(file + "map.txt", std::ios::in | std::ios::binary);
    for (int r = 0; r < 78; r++)
        fs.getline(TileMap[r], DIM2 + 3, '\n');
    fs.close();
}

void RandomGold(){
    int Gold = 25;
    int coordX = 0, coordY = 0;
    srand(time(0));
    while(Gold != 0)
    {
        coordX = 1 + rand() % (DIM1 - 1);
        coordY = 1 + rand() % (DIM2 - 1);
        if (TileMap[coordX][coordY] == '.') TileMap[coordX][coordY] = 'S';
        Gold--;
    }
}

