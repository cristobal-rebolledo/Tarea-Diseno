#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <omp.h>
using namespace std;

long long count = 0;

void creaEscalera(vector<int> &E, int n, int p, int r);
void pisandoEscalones(vector<int>E, vector<int>& saltos, vector<int>& pisar, int objetivo, int ac , vector<int>& menor);
int pisandoEscalonesPD(vector<int>E, vector<int>& saltos,int n, int k);
void imprimir(vector<int>& pisar);


int main(int argc, char **argv){
	int n, p, k = 0;
	if(argc != 4){
		cout << "Error. Debe ejecutarse como ./problema1 n p seed" << endl;
		exit(EXIT_FAILURE);
	}

	n = atoi(argv[1]);
	p = atoi(argv[2]);
	srand(atoi(argv[3]));
	vector<int> E(n);

	int r = rand() % (n - 1) + 1;
	cout <<"El r: " << r << endl;

	creaEscalera(E, n, p, r);
	
	// pone en el vector saltos las potencias de p a la k 
	vector<int> saltos;
	while(pow(p, k) <= n){
		saltos.push_back(pow(p, k));
		k++;
	}
	k--;

	for(int i = 0; i < n;i++)
		cout << E[i] << " " ;
	cout << endl;
	cout << endl;

    vector<int> pisar; // vector que guarda los saltos para llegar a n
	double t1 = omp_get_wtime();
	vector<int> menor;   // vector que guarda la menor cantidad de saltos para llegar a n
	
	pisandoEscalones(E, saltos, pisar,n, 0,menor);   // funcion fuerza bruta
	
	double t2 = omp_get_wtime();
	double tiempo = t2 - t1;

	cout << "Menor cantidad de saltos: " << endl;;
	for (int i = 0; i < (int)menor.size(); i++) 
        cout << menor[i] << " ";
	cout << endl;
	cout << "\nTiempo fuerza bruta: " << tiempo << "s" << endl;
	cout << "Con " << count << " soluciones." << endl;
		
	
    double t3 = omp_get_wtime();
	int cantidadSaltos = pisandoEscalonesPD(E, saltos, n, k);
	double t4 = omp_get_wtime();
	double tiempo2 = t4 - t3;
	cout << "\nTiempo PD: " << tiempo2 << "s" << endl;

	
	cout << endl;
	cout << "Número de formas de llegar al escalón " << n << ": " << cantidadSaltos<< endl;
	cout << endl;
	cout << "\n### Problema 1 ###" << endl;
	return EXIT_SUCCESS;
}

void creaEscalera(vector<int> &E, int n, int p, int r){
	for(int i = 0 ; i < n;i++){
		E[i] = 1;
	}
	
	for(int i = 0; i < r;i++){
		int aleatorio = rand() % (n - 1);
		while(E[aleatorio] == 0)
			aleatorio = rand() % (n - 1);
		E[aleatorio] = 0;
	}
}

void pisandoEscalones(vector<int> E, vector<int>& saltos, vector<int>& pisar, int n,  int ac, vector<int>& menor) {
    if (ac == n) {
		
		if(menor.size() == 0 || pisar.size() < menor.size())  // actualiza la menor cantidad de saltos
			menor = pisar;
			
		ac = 0;
		count++;
        
    } else  {  
        // Continuar explorando posibilidades
        for (int i = 0;  i< (int) saltos.size();i++) {
			if(E[ac+saltos[i]-1] == 1){
				pisar.push_back(ac+saltos[i]);
				pisandoEscalones(E, saltos, pisar, n,  ac + saltos[i], menor);
				pisar.pop_back();
			}
		}

    }
}


int pisandoEscalonesPD(vector<int>E, vector<int>& saltos,int n, int k){
	long long *A = new long long[n];
	for(int i = 0; i < n; i++)
		A[i] = 0;
	for (int j = 0; j<(int)saltos.size();j++){
		if (saltos[j]-1<=n && E[saltos[j]-1]!=0){
			A[saltos[j]-1]=1;
		}
	}
	for (int i = 0; i < n; i++) {
        for (int j = 0; j < (int)saltos.size(); j++) {
            if (i - saltos[j] >= 0 && E[i-saltos[j]] == 1) {
                A[i] += A[i - saltos[j]];
            }
        }
    }

	return A[n-1];
}

void imprimir(vector<int>& pisar){
	count++;
    cout << "-Forma " << count  << ": pisando los escalones: "; 
    for (int i = 0; i < (int)pisar.size(); i++){
    	cout << pisar[i] << " ";
	}
	//cout << endl;
}
