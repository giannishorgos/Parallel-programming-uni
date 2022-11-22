#include <stdio.h>
#include <stdlib.h>
#include "mmio.h"

#define SIZE 8

void printGraph(int graph[SIZE][SIZE]) {
        int row, col;
    for(row = 0; row < SIZE; row++) {
        for(col = 0; col < SIZE; col++) {
            if(graph[row][col]){
                printf("Node:   %d -> %d\twith color: %d\n", row, col, graph[row][col]);
            }
        }
    }
}

void _initColor(int graph[SIZE][SIZE], int colors[SIZE]) {
    for(int row = 0; row < SIZE; row++) {
        for(int col = 0; col < SIZE; col++) {
            graph[row][col] = graph[row][col] ? colors[rand() % SIZE] : 0;
        }
    }
}

int coloringSCCAlgorithm(int graph[SIZE][SIZE], int colors[SIZE]) {
    time_t t;
    srand((unsigned) time(&t));


    char graphIsNotEmpty_bool = 1;
    while (graphIsNotEmpty_bool) {
        _initColor(graph, colors);
        printGraph(graph);
        graphIsNotEmpty_bool = 0;
    }
    return 1;
}


void freeMemory(int** graph) {
    for(int i = 0; i < SIZE; i++) {
        free(graph[i]);
    }
    free(graph);
}


int main(int argc, char* argv[]) {
    // FILE* mtx_file;
    // char* base_path;
    // int base_path_length = 14;
    // base_path = (char*)malloc(base_path_length * sizeof(char));
    // base_path = "graphs_to_use/";
    // if(argc < 2) {
    //     printf("Provide a file !");
    //     exit(1);
    // }


    int colors[SIZE] = {1, 2, 3, 4, 5, 6, 7, 8};
    int graph[SIZE][SIZE] = {
        {0, 1, 0, 0, 0, 0, 0, 0}, 
        {0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 1, 1, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 1, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    

    coloringSCCAlgorithm(graph, colors);
    

    // freeMemory(graph);
    
    return 0;
}