#include <iostream>
#include <cstdlib>
using namespace std;


int main(int argc, char **argv){
	int n;
	if(argc != 3){
		cout << "Error. Debe ejecutarse como ./problema1 n p" << endl;
		exit(EXIT_FAILURE);
	}

	n = atoi(argv[1]);
	
	int *E = new int[n];

	
	for(int i = 0 ; i < n;i++){
		E[i] = 1;
	}

	int r = rand() % (n - 1) + 1;
	cout <<"El r: " << r << endl;
	
	for(int i = 0; i < r;i++){
		E[rand() % (n - 1)] = 0;
	}
	for(int i = 0; i < n;i++)
		cout << E[i] << " " ;

	/*for(int i = 0; i < n; i++)
		cout << E[i] << endl;*/

	
	
	

	cout << "\n### Problema 1 ###" << endl;
	return EXIT_SUCCESS;
}