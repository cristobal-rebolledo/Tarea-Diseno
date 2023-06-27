#include <limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <omp.h>
#include <algorithm>
using namespace std;

void CrearGrafoCiudad(vector<vector<int>>& G, int n);
void declararPuertos(vector<int>& p, int k, int n);
void CrearGrafoIslas(vector<vector<int>>& G, int m);
void imprimirGrafos(vector<vector<int>>& G, int n);
void DefCosto(vector<vector<int>>& B, int k, int b);
void Solucion(vector<vector<int>>& Costo, vector<int>& p, vector<int>& a, vector<int>& DijC, vector<int>& DijI, int r, int k);

int minDistance(vector<int>& dist, bool sptSet[], int V);
void printSolution(vector<int>& dist, int V);
vector<int> dijkstra(vector<vector<int>>& graph, int src, int V);

int main(int argc, char **argv) {

	int n, m, k = 0;
	if(argc != 5 || atoi(argv[1]) <= atoi(argv[3])){
		cout << "Error. Debe ejecutarse como ./problema1 n m k seed. y n>k" << endl;
		exit(EXIT_FAILURE);
	}

	n = atoi(argv[1]); //numero de ciudades
	m = atoi(argv[2]); //numero de islas
	k = atoi(argv[3]); //numero de puertos
	srand(atoi(argv[4]));
	int barcos = log2(m);

	//creacion del grafo

	vector<vector<int>> GrafoCiudad(n,vector<int>(n));

	vector<vector<int>> GrafoIslas(m,vector<int>(m));

    CrearGrafoCiudad(GrafoCiudad, n);

	CrearGrafoIslas(GrafoIslas, m);

    vector<int> puertos(k);

	vector<int> Aptos(barcos);

	vector<int> DijCiudad(n);

	vector<int> DijIslas(m);

	vector<vector<int>> CostoBarcos(k,vector<int>(barcos));

	declararPuertos(Aptos, barcos, m);

	for(int i = 0; i<barcos;i++){
		cout<<"la isla "<< Aptos[i] << " es apta para recibir barcos" << endl;
	}

	cout << endl;

    declararPuertos(puertos, k, n);

	for(int i = 0; i<k;i++){
		cout<<"la ciudad "<< puertos[i] << " tiene un puerto" << endl;
	}

	cout << endl;

	cout<<"Grafo de la ciudad:"<<endl;

    imprimirGrafos(GrafoCiudad, n);

	cout << endl;

	cout<<"Grafo de las islas:"<<endl;

	imprimirGrafos(GrafoIslas, m);

	cout << endl;

	DefCosto(CostoBarcos, k, barcos);

	cout<<"Costo de los barcos:"<<endl;

	for(int i = 0; i<k; i++){
		for(int j = 0; j<barcos; j++){
			cout<< "la ciudad "<< puertos[i] << " hacia la isla " << Aptos[j] << " tiene un costo de: " << CostoBarcos[i][j]<< endl;
		}
	}
	cout << endl;

	double t1 = omp_get_wtime();

	cout<<"dijkstra de la ciudad:"<<endl;

    DijCiudad = dijkstra(GrafoCiudad, 0, n);

	cout << endl;

	cout<<"dijkstra de las Islas:"<<endl;

	DijIslas = dijkstra(GrafoIslas, 0, m);

	cout << endl;

	Solucion(CostoBarcos, puertos, Aptos, DijCiudad, DijIslas, barcos, k);

	double t2 = omp_get_wtime();

	double tiempo = t2 - t1;

	cout << "\nTiempo : " << tiempo << "s" << endl;
 
    return 0;
    }

void CrearGrafoCiudad(vector<vector<int>>& G, int n) {
	bool connect = true;
	int *connection = new int[n];
	for(int i = 0; i<n; i++){
		connection[i] = 0;
	}
	while(connect == true){
		for(int i = 0; i<n ; i++){
			for(int j = 0; j<n;j++){
				int Aleatorio = rand()%2;
				if(i==j){
					G[i][j] = 0;
				}
				else if(Aleatorio == 1){
					int x = (rand()%20) + 1;
					G[i][j] = x;
					connection[j] = 1;
				}
				else if(Aleatorio == 0 and i==0 and j==n-1){
					int r = (rand()%(n-1)) + 1;
					int x = (rand()%20) + 1;
					G[0][r] = x;
					connection[r] = 1;
				}
				else{
					G[i][j] = 0;
				}
			}
		}
		connect = false;
		for(int j = 0; j < n; j++){
			if(connection[j] != 1){
				connect = true;
			}
		}
	}
}

void CrearGrafoIslas(vector<vector<int>>& G, int m){
	int cont = 0;
	bool connect = true;
	int *connection2 = new int[m];
	while(connect == true){
		cont = 0;
		for(int i = 0; i<m; i++){
			connection2[i] = 0;
		}
		for(int i = 0; i<m ; i++){
			for(int j = cont; j<m;j++){
				int Aleatorio = rand()%2;
				if(i==j){
					G[i][j] = 0;
					G[j][i] = 0;
				}
				else if(Aleatorio == 1){
					int x = (rand()%20) + 1;
					G[i][j] = x;
					G[j][i] = x;
					connection2[j] = 1;
					connection2[i] = 1;
				}
				else if(Aleatorio == 0 and j==m-1){
					int r = (rand()%(m-cont-1)) + 1 + cont;
					int x = (rand()%20) + 1;
					G[j][r] = x;
					G[r][j] = x;
					connection2[r] = 1;
					connection2[j] = 1;
				}
				else{
					G[i][j] = 0;
					G[j][i] = 0;
				}
			}
			cont=cont+1;
		}
		connect = false;
		
		for(int j = 0; j < m; j++){
			if(connection2[j] != 1){
				connect = true;
			}
		}
	}
}

void declararPuertos(vector<int>& p, int k, int n) {
	bool encontrar = true;
	int x;
	vector<int> it;	for(int i = 0; i<k ; i++){
		x = rand()%n;
		while(encontrar){
			if(find(p.begin(), p.end(), x) != p.end() && i != 0){
				x = rand()%n;
			}
			else{
				encontrar =false;
			}
		}
		p[i] = x;
		encontrar = true;
	}
}

void imprimirGrafos(vector<vector<int>>& G, int n) {
    for(int i = 0; i<n ; i++){
		for(int j = 0; j<n;j++){
			cout << G[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void DefCosto(vector<vector<int>>& B, int k, int b){
	for(int i = 0; i<k; i++){
		for(int j = 0; j<b; j++){
			int x = (rand()%41) - 20;
			B[i][j] = x;
		}
	}
}

void Solucion(vector<vector<int>>& Costo, vector<int>& p, vector<int>& a, vector<int>& DijC, vector<int>& DijI, int r, int k){
	int PuertoEco = DijC[p[0]];
	int NP = p[0];
	int IslaEco = DijI[a[0]];
	int NI = a[0];
	int BarcoEco = Costo[0][0];
	int suma;
	int menor = PuertoEco + IslaEco + BarcoEco;
	for(int i = 0; i<k; i++){
		for(int j = 0; j<r; j++){
			suma = DijC[p[i]] + Costo[i][j] + DijI[a[j]];
			if(suma < menor){
				PuertoEco = DijC[p[i]];
				IslaEco =  DijI[a[j]];
				BarcoEco = Costo[i][j];
				NP = p[i];
				NI = a[j];
				menor = PuertoEco + IslaEco + BarcoEco;
			}
		}
	}

	cout << "la ruta mas economica es: " << endl;
	cout << "ciudad: "<< NP << " con un costo de " << PuertoEco << endl;
	cout << "Isla: "<< NI << " con un costo de " << IslaEco <<  endl;
	cout << "el costo del barco fue: "<< BarcoEco << endl;
	cout << "costo total: " << PuertoEco + IslaEco + BarcoEco << endl;


}

//Dijkstra

int minDistance(vector<int>& dist, bool sptSet[], int V){
    int min = INT_MAX, min_index;
 
    for (int v = 0; v < V; v++)
        if (sptSet[v] == false && dist[v] <= min)
            min = dist[v], min_index = v;
 
    return min_index;
}
 
void printSolution(vector<int>& dist, int V) {
    printf("Vertex \t\t Distance from Source\n");
    for (int i = 0; i < V; i++)
        printf("%d \t\t\t\t %d\n", i, dist[i]);
}
 

vector<int> dijkstra(vector<vector<int>>& graph, int src, int V) {
    vector<int> dist(V); 
 
    bool sptSet[V]; 

    for (int i = 0; i < V; i++)
        dist[i] = INT_MAX, sptSet[i] = false;
 
    dist[src] = 0;
 
    for (int count = 0; count < V - 1; count++) {
        int u = minDistance(dist, sptSet, V);
 
        sptSet[u] = true;
 
        for (int v = 0; v < V; v++)
            if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v]){
                dist[v] = dist[u] + graph[u][v];
    }
    }
 
    printSolution(dist, V);
	return dist;
}