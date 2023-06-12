#include <iostream>
#include <cstdlib>
using namespace std;


int main(int argc, char **argv){
	int n, p;
	if(argc != 3){
		cout << "Error. Debe ejecutarse como ./problema1 n p" << endl;
		exit(EXIT_FAILURE);
	}

	n = atoi(argv[1]);
	cout << n << endl;
	
	int *E = new int[n];
	int r = 
	for(int i = 0 ; i < n;i++){
		E[i] = i+1;
	}

	for(int i = 0; i < n; i++)
		cout << E[i] << endl;

	
	
	

	cout << "### Problema 1 ###" << endl;
	return EXIT_SUCCESS;
}