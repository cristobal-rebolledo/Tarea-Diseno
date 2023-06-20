#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <omp.h>
using namespace std;

long long count = 0;

void pisandoEscalones(long long *E, vector<long long>& saltos, vector<long long>& pisar, long long objetivo, long long ac);
long long pisandoEscalonesPD(long long *E, vector<long long>& saltos,long long n, long long k);
void imprimir(vector<long long>& pisar);


int main(int argc, char **argv){
	long long n, p, k = 0;
	if(argc != 3){
		cout << "Error. Debe ejecutarse como ./problema1 n p" << endl;
		exit(EXIT_FAILURE);
	}

	n = atoi(argv[1]);
	p = atoi(argv[2]);
	
	long long *E = new long long[n];

	
	for(long long i = 0 ; i < n;i++){
		E[i] = 1;
	}

	long long r = rand() % (n - 1) + 1;
	cout <<"El r: " << r << endl;
	
	for(int i = 0; i < r;i++){
		int aleatorio = rand() % (n - 1);
		while(E[aleatorio] == 0)
			aleatorio = rand() % (n - 1);
		E[aleatorio] = 0;
	}
	
	vector<long long> saltos;
	while(pow(p, k) <= n){
		saltos.push_back(pow(p, k));
		//cout << saltos[k] << " ";
		k++;
	}

	for(long long i = 0; i < n;i++)
		cout << E[i] << " " ;
	cout << endl;
	cout << endl;
	k--;
	//cout << k << endl;

    vector<long long> pisar; 
	//long long ac = 0;
	double t1 = omp_get_wtime();
	//pisandoEscalones(E, saltos, pisar,n, 0);
	double t2 = omp_get_wtime();
	double tiempo = t2 - t1;
	cout << "\nTiempo fuerza bruta: " << tiempo << "s" << endl;
	cout << "Con " << count << " soluciones." << endl;
		
      // Caso base: hay una forma de llegar al escalón 0
	
    // Calcular el número de formas de llegar a cada escalón utilizando programación dinámica
    double t3 = omp_get_wtime();
	long long cantidadSaltos = pisandoEscalonesPD(E, saltos, n, k);
	double t4 = omp_get_wtime();
	double tiempo2 = t4 - t3;
	cout << "\nTiempo PD: " << tiempo2 << "s" << endl;

	
	cout << endl;
	cout << "Número de formas de llegar al escalón " << n << ": " << cantidadSaltos<< endl;
	cout << endl;
	cout << "\n### Problema 1 ###" << endl;
	return EXIT_SUCCESS;
}

void pisandoEscalones(long long *E, vector<long long>& saltos, vector<long long>& pisar, long long n,  long long ac) {
    if (ac == n) {
        // Se ha llegado al objetivo, imprimir el camino encontrado
		
		//imprimir(pisar);
		/*
        cout << "-Forma " << count  << ": pisando los escalones: "; 
        for (long long i = 0; i < (long long)pisar.size(); i++) 
            cout << pisar[i] << " ";*/
        
		ac = 0;
		++count;
		//cout << endl;
        
    } else  {  
        // Continuar explorando posibilidades
        for (long long i = 0;  i< (long long) saltos.size();i++) {
			if(E[ac+saltos[i]-1] != 0){
				//pisar.push_back(ac+saltos[i]);
				pisandoEscalones(E, saltos, pisar, n,  ac + saltos[i]);
				//pisar.pop_back();
			}
        }
    }
}


long long pisandoEscalonesPD(long long *E, vector<long long>& saltos,long long n, long long k){
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

void imprimir(vector<long long>& pisar){
	count++;
    cout << "-Forma " << count  << ": pisando los escalones: "; 
    for (long long i = 0; i < (long long)pisar.size(); i++) 
    	cout << pisar[i] << " ";
	//cout << endl;
}