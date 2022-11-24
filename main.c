#include <stdio.h>
#include <stdlib.h>
#include "mmio.h"

#define NUM_OF_NODES 10

void printGraph(int graph[3][NUM_OF_NODES]) {
    for(int node = 0; node < NUM_OF_NODES; node++) {
        printf("Node:   %d -> %d\twith color: %d\n", graph[0][node], graph[1][node], graph[2][node]);

    }
}


int max(int a, int b) {
    return a > b ? a : b;
}

int* findUniqueColors(int graph[3][NUM_OF_NODES]) {
    int length = 1;
    int used = 0;
    int* unique_colors = (int*)malloc(length * sizeof(int));

    for(int i = 0; i < NUM_OF_NODES; i++) {
        if(used != 0) {
            char unique = 1;
            for(int j = 0; j < used; j++) {
                if(graph[2][i] == unique_colors[j])
                    unique = 0;
            }
            if(unique) {
                if(used >= length) {
                    length += 5;
                    unique_colors = (int*)realloc(unique_colors, length * sizeof(int));
                    unique_colors[used++] = graph[2][i];
                }
                else {
                    unique_colors[used++] = graph[2][i];
                }
            }
        }
        else {
            unique_colors[used++] = graph[2][0];
        }
    }
    return unique_colors;
}

int* findSCC(int graph[3][NUM_OF_NODES]) {
    int counter_scc = 0;
    for(int index = 0; index < NUM_OF_NODES; index++) {
        findUniqueColors(graph);
    }
}

int coloringSCCAlgorithm(int graph[3][NUM_OF_NODES]) {
    /*
        DESC
        ----------
        Get a directed graph as input and output the all SCC

        PARAMETERS
        ----------
        a directed graph

        Returns
        ----------
        a list with all SCC
    */
    char color_changed = 1; // boolean value, 1 -> True, 0 -> False

    printGraph(graph);
    while (color_changed != 0) { // while at least one color is changed
        color_changed = 0; // init with 0, ie no color is changed

        // if (noramal_x, normal_y) == (0, 1) -> traverse the graph FORWARD
        // if (noramal_x, normal_y) == (1, 0) -> traverse the graph BACKWARD
        int normal_x = 0; 
        int normal_y = 1;

        for(int node = 0; node < NUM_OF_NODES; node++){
            for(int neigh_node = 0; neigh_node < NUM_OF_NODES; neigh_node++) {
                if(graph[normal_y][neigh_node] == graph[normal_x][node]) { // find all vertices that point to a node
                    // change the color of the neighboring node 
                    // if the color is greater than the node that is pointing to.
                    if(max(graph[2][neigh_node], graph[2][node]) == graph[2][node] 
                        && max(graph[2][neigh_node], graph[2][node]) != graph[2][neigh_node]
                        && graph[2][node] != -1 
                        && graph[2][neigh_node] != -1) { 
                        graph[2][neigh_node] = max(graph[2][neigh_node], graph[2][node]);
                        color_changed = 1;
                        printf("Mpainw gia %d fora x %d\n", neigh_node, node);
                    }
                }
            }
        }
        printf("==============================\n");
        int temp_x = normal_x;
        normal_x = normal_y;
        normal_y = temp_x;
    }
    printGraph(graph);

    // findSCC(graph);
    int* unique_colors = findUniqueColors(graph);
    for(int i = 0; i < NUM_OF_NODES; i++) {
        printf("unique colors are: %d\n", unique_colors[i]);
    }
    return 1;
}


void freeMemory(int** graph) {
    for(int i = 0; i < NUM_OF_NODES; i++) {
        free(graph[i]);
    }
    free(graph);
}


int main(int argc, char* argv[]) {
    // Shape of sparse matrix
    // {0, 82, 0, 0, 0, 0, 0, 0}, 
    // {0, 0, 56, 0, 0, 0, 0, 0},
    // {0, 0, 0, 34, 34, 0, 0, 0},
    // {20, 0, 0, 0, 0, 0, 0, 0},
    // {0, 0, 0, 0, 0, 12, 0, 0},
    // {0, 0, 0, 0, 0, 0, 34, 0},
    // {0, 0, 0, 0, 45, 0, 0, 45},
    // {0, 0, 0, 0, 0, 0, 0, 0}


    // int row_coo[NUM_OF_NODES] = [0, 1, 2, 2, 3, 4, 5, 6, 6, 7]
    // int col_coo[NUM_OF_NODES] = [1, 2, 3, 4, 0, 5, 6, 4, 7, -1]
    // int values[NUM_OF_NODES] = [82, 56, 34, 98, 20, 12, 34, 45, 89, -1]

    int graph[3][NUM_OF_NODES] = {
        {0, 1, 2, 2, 3, 4, 5, 6, 6, 7}, // row coordinate
        {1, 2, 3, 4, 0, 5, 6, 4, 7, -1}, // col coordinate
        {82, 56, 34, 34, 20, 12, 34, 45, 45, -1} // value
    };




    
    // printGraph(graph);
    coloringSCCAlgorithm(graph);
    

    // freeMemory(graph);
    
    return 0;
}