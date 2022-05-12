#include "CampoMinado.hpp"
#include <iostream>
#include <gtkmm/button.h>
#include <gtkmm/widget.h>
#include <math.h>
#include <gtkmm/image.h>


CampoMinado::CampoMinado():
boxGeral(Gtk::ORIENTATION_VERTICAL,0),
 boxSuperior(Gtk::ORIENTATION_HORIZONTAL,0),
 boxJogo(Gtk::ORIENTATION_HORIZONTAL,0),
 botaoNovoJogo("Novo Jogo"),
 botaoAjuda("Ajuda"),
 botaoSair("Sair"),
 iniciante("Iniciante"),
 intermediario("Intermediário"),
 avancado("Avançado"),
 dificuldade(0)
  {


  set_default_size(1024,768);
  set_title("Campo minado Jardel e Micaelli");

  botaoNovoJogo.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,&CampoMinado::on_iniciarJogo), dificuldade));

  botaoSair.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,&CampoMinado::on_clickedClose), 0));

  iniciante.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,&CampoMinado::on_defineNivel), 0));
  intermediario.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,&CampoMinado::on_defineNivel), 1));
  avancado.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,&CampoMinado::on_defineNivel), 2));

/*

  add(fixed);
  fixed.add(frame1);
  fixed.move(frame1,0,0);


  intermediario.join_group(iniciante);
  avancado.join_group(iniciante);

  boxSuperior.set_homogeneous(true);
  boxGeral.pack_start(boxJogo);





  boxSuperior.pack_start(botaoNovoJogo);
  boxSuperior.pack_start(botaoAjuda);

  boxSuperior.pack_start(iniciante);
  boxSuperior.pack_start(intermediario);
  boxSuperior.pack_start(avancado);
  boxSuperior.pack_start(botaoSair);
  
  frame1.add(boxSuperior);

 


  for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			Gtk::Button* pButton = new Gtk::Button("",true);
      (*pButton).signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,&CampoMinado::on_clicked), i,j));
		  gridJogo.attach(*pButton,i,j,1,1);
		}
		
	}

  

    */
on_iniciarJogo(1);
  
  add(gridJogo);

  gridJogo.set_column_homogeneous(true);



  show_all_children();

  

}

void CampoMinado::on_clicked(int positionX,int positionY)
{
  Gtk::Widget* pWidget =  gridJogo.get_child_at(positionX,positionY);
  Gtk::Button* pBt = dynamic_cast<Gtk::Button*>(pWidget); 
  (*pBt).set_always_show_image(true);

}

void CampoMinado::on_iniciarJogo(int dif)
{

 switch (dif)
 {
 case 0:
  for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			Gtk::Button* pButton = new Gtk::Button("",false);
      (*pButton).signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,&CampoMinado::on_clicked), i,j));
		  Gtk::Image* icon = new Gtk::Image;
       icon->set("bamba.png");
      (*pButton).set_image(*Gtk::manage(icon));
      (*pButton).set_always_show_image(false);
      gridJogo.attach(*pButton,i,j,1,1);
		}
		
	}
   break;

   case 1:

  for(int i=0;i<15;i++){
		for(int j=0;j<15;j++){
			Gtk::Button* pButton = new Gtk::Button("",false);
      (*pButton).signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,&CampoMinado::on_clicked), i,j));
		  Gtk::Image* icon = new Gtk::Image;
       icon->set("bamba.png");
      (*pButton).set_image(*Gtk::manage(icon));
      (*pButton).set_always_show_image(false);
      gridJogo.attach(*pButton,i,j,1,1);
		}		
	}

   break;

   case 2:

     for(int i=0;i<15;i++){
		for(int j=0;j<30;j++){
			Gtk::Button* pButton = new Gtk::Button("",false);
      (*pButton).signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,&CampoMinado::on_clicked), i,j));
		  Gtk::Image* icon = new Gtk::Image;
       icon->set("bamba.png");
      (*pButton).set_image(*Gtk::manage(icon));
      (*pButton).set_always_show_image(false);
      gridJogo.attach(*pButton,i,j,1,1);
		}		
	}

   break;
 
 default:

  for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			Gtk::Button* pButton = new Gtk::Button("",false);
      (*pButton).signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,&CampoMinado::on_clicked), i,j));
		  Gtk::Image* icon = new Gtk::Image;
       icon->set("bamba.png");
      (*pButton).set_image(*Gtk::manage(icon));
      (*pButton).set_always_show_image(false);
      gridJogo.attach(*pButton,i,j,1,1);
		}
		
	}


   break;
 }


}


void CampoMinado::on_defineNivel(int dif)
{
dificuldade=dif;
  on_iniciarJogo(dificuldade);
}




void CampoMinado::on_clickedClose(int r)
{
   close();
}



void preencher(std::vector<std::vector<int>> & vet, int linhas, int colunas, int bombas){

  unsigned seed =time(0);
  srand(seed);
   
  for (int quantidade=0; quantidade<bombas; 
    quantidade++){
      
		int i= rand() % linhas ; //escolha aleatória da linha 
   	int j= rand() % colunas; //escolha aleatória da coluna
      vet[i][j]=-1;  //colocação da bomba 
	}

for (int i=0; i<linhas;  i++){
  for (int k=0; k<colunas;  k++){
    
    if (vet[i][k]==-1){ //possui bomba (-1)
             if (i-1>=0){ 
              if (vet[i-1][k]!=-1)
                vet[i-1][k]++;
              
             }
          
            if (i+1<linhas){
              if (vet[i+1][k]!=-1)
                vet[i+1][k]++;
              
            }
            if (k-1>=0){
              if (vet[i][k-1]!=-1)
                vet[i][k-1]++; }
      
            if (k+1 < colunas){
              if (vet[i][k+1]!=-1)
                vet[i][k+1]++;
              
              }

           if (i-1>= 0 && k-1 >= 0){
              if (vet[i-1][k-1]!=-1)
                vet[i-1][k-1]++;
              
              }

            if (i-1>= 0 && k+1 < colunas){
              if (vet[i-1][k+1]!=-1)
                vet[i-1][k+1]++;
            }

            if (i+1 < linhas && k-1 >= 0) {
              if (vet[i+1][k-1]!=-1)
                vet[i+1][k-1]++;
            }

            if (i+1 < linhas && k+1 < colunas){
              if (vet[i+1][k+1]!=-1)
                vet[i+1][k+1]++;
              
            }    
    }   
  }
}
 //imprimir(vet, linhas, colunas);   
}
   

void gerar_mapa(std::vector<std::vector<int>> & vet, int linhas, int colunas, int bomba){ //inicializa o mapa com valores zeros
  
  for(int y=0;y<linhas;y++){
    // vetor que representa uma linha
    std::vector<int> linha;
    for(int x=0;x<colunas;x++){
      linha.push_back(0);
    }
    vet.push_back(linha);
  }
   
 
 // preencher( vet, linhas, colunas, bomba);
 
}
