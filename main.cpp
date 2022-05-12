 #include <iostream>
 #include <time.h>
 #include "Celula.h"
 #include <vector>

//enum  { beginner, intermediary, advanced };


std::vector <std::vector<celula>> celulas;




void iniciante (){
	int L=10, C=10; 
    char matriz[L][C];
	int bombas=10;


    


 srand(time(NULL));
	for (int quantidade=0; quantidade<bombas; quantidade++){

		int i= rand() & L;
		int j= rand() & C;
		matriz[i][j]=='X';
	}






}

void intermediario (){
	int L=15, C=15; 
    char matriz[L][C];
	int bombas=40;


 srand(time(NULL));
	for (int quantidade=0; quantidade<bombas; quantidade++){

		int i= rand() & L;
		int j= rand() & C;
		matriz[i][j]=='X';
	}



}




void avancado(){

int L=15, C=30; 
    char matriz[L][C];
	int bombas=100;


 srand(time(NULL));
	for (int quantidade=0; quantidade<bombas; quantidade++){

		int i= rand() & L;
		int j= rand() & C;
		matriz[i][j]=='X';
	}


}


void imprimirInterface(){

}

int main (int argc, char **argv)
{
    
	char action=*argv[1]; 
   
	

	switch (action){
       case '1': /*iniciante();*/
       std::cout << "iniciante" << std::endl;
	   break;

	   case '2': intermediario();
	   break;

	   case '3': avancado();
	   break;
	}

	


	return 0;
}