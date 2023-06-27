#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <omp.h>
using namespace std;

long long count = 0;   // variable global para algoritmo de fuerza bruta

void creaEscalera(vector<int> &E, int n, int p, int r);
void pisandoEscalones(vector<int>E, vector<int>& saltos, vector<int>& pisar, int objetivo,long long ac , vector<int>& menor , int k);
int pisandoEscalonesPD(vector<int>E, vector<int>& saltos,int n, int k);


int main(int argc, char **argv){
	int n, p, r, k = 0;
	
	if(argc != 5 || atoi(argv[3]) >= atoi(argv[1])){
		cout << "Error. Debe ejecutarse como ./problema1 n p r seed" << endl;
		exit(EXIT_FAILURE);
	}

	n = atoi(argv[1]);
	p = atoi(argv[2]);
	r = atoi(argv[3]);
	srand(atoi(argv[4]));
	
	vector<int> E(n);

	creaEscalera(E, n, p, r);
	
	// pone en el vector saltos las potencias de p a la k 
	vector<int> saltos;
	while(pow(p, k) <= n){
		saltos.push_back(pow(p, k));
		k++;
	}
	
	cout << "Escalera generada: \n" << endl;
	for(int i = 0; i < n;i++)
		cout << E[i] << " " ;
	cout << endl;

    vector<int> pisar; // vector que guarda los saltos para llegar a n
	vector<int> menor;   // vector que guarda la menor cantidad de saltos para llegar a n
	
	cout << "\n## FUERZA BRUTA ## " << endl;

	double t1 = omp_get_wtime();

	pisandoEscalones(E, saltos, pisar,n, 0,menor,k);   // funcion fuerza bruta
	
	double t2 = omp_get_wtime();
	double tiempo = t2 - t1;
	
	cout << "\nTiempo fuerza bruta: " << tiempo << "s" << endl;
	
	cout << "\nNúmero de formas de llegar al escalón " << n << " : " << count << endl;
		
	cout << "\n## PROGRAMACIÓN DINÁMICA ## " << endl;
	
	double t3 = omp_get_wtime();
	
	int cantidadSaltos = pisandoEscalonesPD(E, saltos, n, k);  // funcion PD
	
	double t4 = omp_get_wtime();
	double tiempo2 = t4 - t3;
	
	cout << "\nTiempo PD: " << tiempo2 << "s" << endl;

	cout << "\nNúmero de formas de llegar al escalón " << n << " : " << cantidadSaltos << endl;

	cout << "\nMenor cantidad de saltos: " << endl;;
	
	for (int i = 0; i < (int)menor.size(); i++) // imprime menor cantidad de saltos
        cout << menor[i] << " ";
	
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

void pisandoEscalones(vector<int> E, vector<int>& saltos, vector<int>& pisar, int n,  long long ac, vector<int>& menor, int k) {
    if (ac == n) {
		
		if( menor.size() == 0 || pisar.size() < menor.size())  // actualiza la menor cantidad de saltos
			menor = pisar;
		
		ac = 0;
		count++;
        
    } else  {  
		
        for (int i = 0;  i < k; i++) {
			if((ac + saltos[i] <= n) && (E[ ac + saltos[i] - 1] == 1)){
				pisar.push_back(ac+saltos[i]);
				pisandoEscalones(E, saltos, pisar, n,  ac + saltos[i], menor, k);
				pisar.pop_back();
			}
		}

    }
}


int pisandoEscalonesPD(vector<int>E, vector<int>& saltos,int n, int k){
	long long *A = new long long[n];
	
	for(int i = 0; i < n; i++)
		A[i] = 0;
	
	for (int j = 0; j < k ; j++){
		if ( (saltos[j] - 1 <= n ) && (E[ saltos[j]- 1] != 0)){
			A[saltos[j]-1]=1;
		}
	}
	
	for (int i = 0; i < n; i++) {
        for (int j = 0; j < k ; j++) {
            if ((i - saltos[j] >= 0) && (E[ i- saltos[j]] == 1)) {
                A[i] += A[i - saltos[j]];
            }
        }
    }

	return A[n-1];
}

