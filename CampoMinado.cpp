#include "CampoMinado.hpp"
#include <iostream>
#include <gtkmm/button.h>
#include <gtkmm/widget.h>
#include <math.h>
#include <gtkmm/image.h>


CampoMinado::CampoMinado():
boxGeral(Gtk::ORIENTATION_VERTICAL,0),
 boxSuperior(Gtk::ORIENTATION_VERTICAL,0),
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
  Gtk::Image* iconNovoJogo = new Gtk::Image;
  iconNovoJogo->set("jogar.png");
  botaoNovoJogo.set_image(*Gtk::manage(iconNovoJogo));
  botaoNovoJogo.set_always_show_image(true);

  botaoAjuda.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,&CampoMinado::on_clickedAjuda), 0));
  Gtk::Image* icon = new Gtk::Image;
  icon->set("lampada.png");
  botaoAjuda.set_image(*Gtk::manage(icon));
  botaoAjuda.set_always_show_image(true);

  botaoSair.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,&CampoMinado::on_clickedClose), 0));
  Gtk::Image* iconSair = new Gtk::Image;
  iconSair->set("sair.png");
  botaoSair.set_image(*Gtk::manage(iconSair));
  botaoSair.set_always_show_image(true);


  iniciante.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,&CampoMinado::on_defineNivel), 0));
  intermediario.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,&CampoMinado::on_defineNivel), 1));
  avancado.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,&CampoMinado::on_defineNivel), 2));


 
  add(pane);
  pane.add1(fixed);
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



 pane.add2(gridJogo);

  
  


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

 switch (dificuldade)
 {



 case 0:
    for(int i=10;i>0;i--){
     gridJogo.remove_row(i);	
	}

   if(iniciante.get_active()){

  for(int i=0;i<10;i++){
		for(int j=0;j<10;j++){
			Gtk::Button* pButton = new Gtk::Button("",false);
      (*pButton).signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,&CampoMinado::on_clicked), i,j));
		  Gtk::Image* icon = new Gtk::Image;
       icon->set("trevo.png");
      (*pButton).set_image(*Gtk::manage(icon));
      (*pButton).set_always_show_image(false);
      (*pButton).set_use_underline(true);
      gridJogo.attach(*pButton,i,j,1,1);
		}		
	}

   }else if(intermediario.get_active()){
    for(int i=0;i<15;i++){
		for(int j=0;j<15;j++){
			Gtk::Button* pButton = new Gtk::Button("",false);
      (*pButton).signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,&CampoMinado::on_clicked), i,j));
		  Gtk::Image* icon = new Gtk::Image;
       icon->set("trevo.png");
      (*pButton).set_image(*Gtk::manage(icon));
      (*pButton).set_always_show_image(false);
      gridJogo.attach(*pButton,i,j,1,1);
		}		
	}
   }else{

  for(int i=0;i<15;i++){
		for(int j=0;j<30;j++){
			Gtk::Button* pButton = new Gtk::Button("",false);
      (*pButton).signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,&CampoMinado::on_clicked), i,j));
		  Gtk::Image* icon = new Gtk::Image;
       icon->set("trevo.png");
      (*pButton).set_image(*Gtk::manage(icon));
      (*pButton).set_always_show_image(false);
      gridJogo.attach(*pButton,i,j,1,1);
		}		
	}

   }

  
   break;

   case 1:

    for(int i=15;i>0;i--){
     gridJogo.remove_row(i);	
	}

   if(iniciante.get_active()){

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

   }else if(intermediario.get_active()){
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
   }else{

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

   }

   break;

   case 2:


    for(int i=15;i>0;i--){
     gridJogo.remove_row(i);	
	}

   if(iniciante.get_active()){

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

   }else if(intermediario.get_active()){
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
   }else{

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

   }

   break;
 
 default:



   break;
 }

 show_all_children();


}


void CampoMinado::on_defineNivel(int dif)
{
//dificuldade=dif;
}

void CampoMinado::on_clickedAjuda(int a)
{

Gtk::MessageDialog dialog(*this, "Informações sobre o jojo");
  dialog.set_secondary_text(" O jogo consiste em uma área matricial de n linhas por m colunas com um total de n * m células e k minas. Inicialmente, as células estão ocultas, ou seja, não é possível determinar se ela possui uma mina ou não, e o objetivo do jogo é revelar todas as células que não possuem minas. Assim, uma célula pode ser revelada por uma ação do usuário ou por uma das regras do jogo e isso pode resultar em uma das três situações possíveis:\n\n1 - Uma mina é revelada:\n Nesse caso, o jogo encerra com a derrota do usuário; \n\n2 - Um número é revelado: \n O valor indica a quantidade de minas adjacentes, isto é, a quantidade de minas nas 8 células vizinhas; \n\n3 - Uma posição vazia é revelada:\n nesse caso, o jogo revela automaticamente todas as células adjacentes a essa posição, visto que ela não possui minas adjacentes.\n\n  O usuário vence o jogo ao revelar todas as células que não contêm minas. Além disso, o usuário pode marcar uma célula não revelada com uma bandeira caso ele acredite que não existe uma mina nessa posição. Logo, o usuário pode aplicar a ação revelar sobre um número desde que a quantidade de bandeiras adjacentes seja igual ao seu número. Assim, todas as células adjacentes, que não estão marcadas por bandeiras, são reveladas automaticamente. Observe, que isso ocorrerá mesmo que as bandeiras estejam posicionadas incorretamente e assim revelando uma mina.Por fim, a dificuldade do jogo irá determinar as dimensões da área do jogo, a quantidade de minas e se a primeira ação revelar sempre será um número ou sempre será uma posição vazia.");
  dialog.run();
  
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

