
// C program for Dijkstra's single source shortest path
// algorithm. The program is for adjacency matrix
// representation of the graph
#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <omp.h>
using namespace std;
 
// Number of vertices in the graph
 
// A utility function to find the vertex with minimum
// distance value, from the set of vertices not yet included
// in shortest path tree
int minDistance(int dist[], bool sptSet[], int V)
{
    // Initialize min value
    int min = INT_MAX, min_index;
 
    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
 
    return min_index;
}
 
// A utility function to print the constructed distance
// array
void printSolution(int dist[], int V)
{
    printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t\t\t %d\n", i, dist[i]);
}
 
// Function that implements Dijkstra's single source
// shortest path algorithm for a graph represented using
// adjacency matrix representation
void dijkstra(int **graph, int src, int V)
{
    int dist[V]; // The output array.  dist[i] will hold the
                 // shortest
    // distance from src to i
 
    bool sptSet[V]; // sptSet[i] will be true if vertex i is
                    // included in shortest
    // path tree or shortest distance from src to i is
    // finalized
 
    // Initialize all distances as INFINITE and stpSet[] as
    // false
    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
 
    // Distance of source vertex from itself is always 0
    dist[src] = 0;
 
    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of
        // vertices not yet processed. u is always equal to
        // src in the first iteration.
        int u = minDistance(dist, sptSet, V);
 
        // Mark the picked vertex as processed
        sptSet[u] = true;
 
        // Update dist value of the adjacent vertices of the
        // picked vertex.
        for (int v = 0; v < V; v++)
 
            // Update dist[v] only if is not in sptSet,
            // there is an edge from u to v, and total
            // weight of path from src to  v through u is
            // smaller than current value of dist[v]
            if (!sptSet[v] && graph[u][v]
                && dist[u] != INT_MAX
                && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
 
    // print the constructed distance array
    printSolution(dist, V);
}

// driver's code
int main(int argc, char **argv)
{
    /* Let us create the example graph discussed above */
	int n, m, k = 0;
	if(argc != 4 || atoi(argv[1]) <= atoi(argv[3])){
		cout << "Error. Debe ejecutarse como ./problema1 n m k. y n>k" << endl;
		exit(EXIT_FAILURE);
	}

	n = atoi(argv[1]); //numero de ciudades
	m = atoi(argv[2]); //numero de islas
	k = atoi(argv[3]); //numero de puertos
	int recibir = log2(k);
	int barcos = log2(m);

	//creacion del grafo
	int** GrafoCiudad = new int*[n];
    for (int i = 0; i < n; i++){
        GrafoCiudad[i] = new int[n];
    }
	for(int i = 0; i<n ; i++){
		for(int j = 0; j<n;j++){
			int eleatorio = rand()%2;
			if(i==j){
				GrafoCiudad[i][j] = 0;
			}
			else if(eleatorio == 1){
				int x = (rand()%20) + 1;
				GrafoCiudad[i][j] = x;
			}
			else{
				GrafoCiudad[i][j] = 0;
			}
		}
	}
	int puertos[k];
	for(int i = 0; i<k ; i++){
		int x = rand()%n;
		puertos[i] = x;
	}
	for(int i = 0; i<n ; i++){
		for(int j = 0; j<n;j++){
			cout << GrafoCiudad[i][j] << " ";
		}
		cout << endl;
	}
 
    // Function call
    dijkstra(GrafoCiudad, 0, n);
 
    return 0;
}