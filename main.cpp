 #include <iostream>
 #include<time>

//enum  { beginner, intermediary, advanced };


void iniciante (){
	int L=10, C=10; 
    char matriz[L][C];
	int bombas=10;


 srand(time(NULL))
	for (int quantidade=0; quantidade<bombas; quantidade++){

		i= rand() & L;
		j= rand() & C;
		matriz[i][j]=='X';
	}






}

void intermediario (){
	int L=15, C=15; 
    char matriz[L][C];
	int bombas=40;


 srand(time(NULL))
	for (int quantidade=0; quantidade<bombas; quantidade++){

		i= rand() & L;
		j= rand() & C;
		matriz[i][j]=='X';
	}



}




void avancado(){

int L=15, C=30; 
    char matriz[L][C];
	int bombas=100;


 srand(time(NULL))
	for (int quantidade=0; quantidade<bombas; quantidade++){

		i= rand() & L;
		j= rand() & C;
		matriz[i][j]=='X';
	}


}



int main (int arg, char **argv)
{
    
	char action; 
   

	std:: cin >> action;  //recebe a ação que o usuario quer realizar; 

	switch (action){
       case 'b': iniciante();
	   break;

	   case 'i': intermediario();
	   break;

	   case 'a': avancado();
	   break;
	}

	


	return 0;
}