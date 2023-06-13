#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
using namespace std;


int main(int argc, char **argv){
	int n, p, k = 0;
	if(argc != 3){
		cout << "Error. Debe ejecutarse como ./problema1 n p" << endl;
		exit(EXIT_FAILURE);
	}

	n = atoi(argv[1]);
	p = atoi(argv[2]);
	
	int *E = new int[n];

	
	for(int i = 0 ; i < n;i++){
		E[i] = 1;
	}

	int r = rand() % (n - 1) + 1;
	cout <<"El r: " << r << endl;
	
	for(int i = 0; i < r;i++){
		int aleatorio = rand() % (n - 1);
		while(E[aleatorio] == 0)
			aleatorio = rand() % (n - 1);
		E[aleatorio] = 0;
		
	}
	for(int i = 0; i < n;i++)
		cout << E[i] << " " ;
	cout << endl;
	
	vector<int> saltos;
	while(pow(p, k) <= n){
		saltos.push_back(pow(p, k));
		cout << saltos[k] << " ";
		k++;
	}
	cout << endl;
	k--;
	cout << k << endl;

	/*for(int i = 0; i < n; i++)
		cout << E[i] << endl;*/

	
	
	

	cout << "\n### Problema 1 ###" << endl;
	return EXIT_SUCCESS;
}