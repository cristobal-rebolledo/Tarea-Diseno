#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include <omp.h>
using namespace std;

long long count = 0;

void pisandoEscalones(long long *E, vector<long long>& saltos, vector<long long>& pisar, long long objetivo, long long ac);


long long* pisandoEscalonesPD(long long *A, long long n,long long k,vector<long long>& saltos,long long c){
	//long long *B = new long long[n];
	//A[1] = 1;
	return A;
}

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
    
	pisandoEscalones(E, saltos, pisar,n, 0);
	double t2 = omp_get_wtime();
	double tiempo = t2 - t1;
	cout << "\nTiempo fuerza bruta: " << tiempo << "s" << endl;
	long long *salt= new long long[k];
	
	vector<long long> pisarPD; 
	//long long *dp= new long long[n+1]

	std::vector<long long> dp(n + 1, 0);
	int s = 0;
	//while(E[s] == 0)s++;
		
    dp[s] = 1;  // Caso base: hay una forma de llegar al escalón 0
	cout << s << endl;
    // Calcular el número de formas de llegar a cada escalón utilizando programación dinámica
    for (long long i = s; i <= n; i++) {
        for (long long j = 0; j < static_cast<long long>(saltos.size()); j++) {
            if (i - saltos[j] >= 0 && E[i - saltos[j]-1] != 0) {
                dp[i] += dp[i - saltos[j]];
            }
        }
    }
	for (long long i = 1; i <= n; i++)
		cout << dp[i] << " ";
	cout << endl;
	cout << "Número de formas de llegar al escalón " << n << ": " << dp[n] << endl;
	cout << endl;
	cout << "\n### Problema 1 ###" << endl;
	return EXIT_SUCCESS;
}

void pisandoEscalones(long long *E, vector<long long>& saltos, vector<long long>& pisar, long long n,  long long ac) {
    if (ac == n) {
        // Se ha llegado al objetivo, imprimir el camino encontrado
		count++;
        cout << "-Forma " << count  << ": pisando los escalones: "; 
        for (long long i = 0; i < (long long)pisar.size(); i++) 
            cout << pisar[i] << " ";
        
		ac = 0;
		cout << endl;
        
    } else  {  
        // Continuar explorando posibilidades
        for (long long i = 0;  i< (long long) saltos.size();i++) {
			if(E[ac+saltos[i]-1] != 0){
				pisar.push_back(ac+saltos[i]);
				pisandoEscalones(E, saltos, pisar, n,  ac + saltos[i]);
				pisar.pop_back();
			}
        }
    }
}