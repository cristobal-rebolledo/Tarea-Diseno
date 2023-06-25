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
 
void CrearGrafoCiudad(vector<vector<int>>& G, int n);
void declararPuertos(vector<int>& p, int k, int n);
void imprimirGrafos(vector<vector<int>>& G, int n);

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
void printSolution(int dist[], int V) {
    printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t\t\t %d\n", i, dist[i]);
}
 

void dijkstra(vector<vector<int>>& graph, int src, int V) {
    int dist[V]; 
 
    bool sptSet[V]; 

    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
 
    // Distance of source vertex from itself is always 0
    dist[src] = 0;
 
    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet, V);
 
        // Mark the picked vertex as processed
        sptSet[u] = true;

        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]){
                dist[v] = dist[u] + graph[u][v];
            }
    }
 
    // print the constructed distance array
    printSolution(dist, V);
}

// driver's code
int main(int argc, char **argv) {
    /* Let us create the example graph discussed above */
	int n, m, k = 0;
	if(argc != 4 || atoi(argv[1]) <= atoi(argv[3])){
		cout << "Error. Debe ejecutarse como ./problema1 n m k. y n>k" << endl;
		exit(EXIT_FAILURE);
	}

	n = atoi(argv[1]); //numero de ciudades
	m = atoi(argv[2]); //numero de islas
	k = atoi(argv[3]); //numero de puertos
	srand(1000);
	int recibir = log2(k);
	int barcos = log2(m);

	//creacion del grafo

    srand(1000);

	vector<vector<int>> GrafoCiudad(n,vector<int>(n));

    CrearGrafoCiudad(GrafoCiudad, n);

    vector<int> puertos(k);

    declararPuertos(puertos, k, n);

    imprimirGrafos(GrafoCiudad, n);

    dijkstra(GrafoCiudad, 0, n);
 
    return 0;
}

void CrearGrafoCiudad(vector<vector<int>>& G, int n) {
    int Aleatorio = rand()%2;
	for(int i = 0; i<n ; i++){
		for(int j = 0; j<n;j++){
			int Aleatorio = rand()%2;
			if(i==j){
				G[i][j] = 0;
			}
			else if(Aleatorio == 1){
				int x = (rand()%20) + 1;
				G[i][j] = x;
			}
			else{
				G[i][j] = 0;
			}
		}
	}
}

void declararPuertos(vector<int>& p, int k, int n) {
    for(int i = 0; i<k ; i++){
		int x = rand()%n;
		p[i] = x;
	}
}

void imprimirGrafos(vector<vector<int>>& G, int n) {
    for(int i = 0; i<n ; i++){
		for(int j = 0; j<n;j++){
			cout << G[i][j] << " ";
		}
		cout << endl;
	}
}