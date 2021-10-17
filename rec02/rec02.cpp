/*
Andre Hu
2/5/2021
Rec02

Simulation for Conway's Game of Life
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

//Searches 8 squares around cell, returns int neighbors
int count_neighbors(const vector<string>& map, int x, int y){
    int neighbors = 0;
    //top-left
    if (map[y - 1][x - 1] == '*'){
        neighbors += 1;
    }
    //top-middle
    if (map[y - 1][x] == '*'){
        neighbors += 1;
    }
    //top-right
    if (map[y - 1][x + 1] == '*'){
        neighbors += 1;
    }
    //left
    if (map[y][x - 1] == '*'){
        neighbors += 1;
    }
    //right
    if (map[y][x + 1] == '*'){
        neighbors += 1;
    }
    //bottom-left
    if (map[y + 1][x - 1] == '*'){
        neighbors += 1;
    }
    //bottom-middle
    if (map[y + 1][x] == '*'){
        neighbors += 1;
    }
    //bottom-right
    if (map[y + 1][x + 1] == '*'){
        neighbors += 1;
    } 
    return neighbors;
}

//Prints map, ignores extra rows/columns
void print(const vector<string>& map){
    for (size_t i = 1; i < map.size() - 1; ++i){
        for (size_t j = 1; j < map[i].size() - 1; ++j){
            cout << map[i][j];
        }
        cout << endl;
    }
    cout << "===========================" << endl;
}

void advance_generation(vector<string>& map){
    
    //stores which cells are alive next generation
    vector<int> x_locations;
    vector<int> y_locations;

    //First iteration find which cells are alive
    for(size_t y = 1; y < map.size() - 1; ++y){
        for(size_t x = 1;  x < map[y].size() - 1; ++x){
            int neighbors = count_neighbors(map, x, y);
            //Dead cell
            if (map[y][x] == '-'){
                if (neighbors == 3){
                    x_locations.push_back(x);
                    y_locations.push_back(y);
                }
            }
            //Alive cell
            else if (map[y][x] == '*'){
                if (neighbors == 2 || neighbors == 3){
                    x_locations.push_back(x);
                    y_locations.push_back(y);
                }
            }
        }
    }

    //Second iteration set all dead cells, 
    //also makes sure borders are still dead cells
    for(size_t y = 0; y < map.size(); ++y){
        for(size_t x = 0;  x < map[y].size(); ++x){
            map[y][x] = '-';
        }
    }

    //Third iteration place alive cells;
    for (size_t i = 0; i < x_locations.size(); ++i){
        map[y_locations[i]][x_locations[i]] = '*';
    }
}

//Initializes cells into map, adds extra rows/columns
void initialize(vector<string>& map, ifstream& life){
    string line;
    string extra_row = "";

    getline(life, line);

    //Determine length of line
    for (size_t i = 0; i < line.size() + 2; ++i){ 
        extra_row += "-";
    }

    map.push_back(extra_row); //top row
    map.push_back("-" + line + "-"); //line already read
    
    while (getline(life, line)){
        map.push_back("-" + line + "-");
    } 

    map.push_back(extra_row); //bottom row
}

int main(){
    //read life.txt
    ifstream life("life.txt");
    if (!life){
        cerr << "failed to open life.txt";
        exit(1);
    }
    

    //variable containing conway cells    
    vector<string> map;
    initialize(map, life);   
    life.close();
    
    //Print and advance generations
    cout << "Initial world" << endl;
    print(map);

    for (size_t i = 1; i < 11; ++i){
        cout << "Generation: " << i << endl;
        advance_generation(map);
        print(map);
    }

    return 0;
}