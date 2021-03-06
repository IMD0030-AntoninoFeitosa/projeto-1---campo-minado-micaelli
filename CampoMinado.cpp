#include "CampoMinado.hpp"
#include <iostream>
#include <gtkmm/button.h>
#include <gtkmm/widget.h>
#include <math.h>
#include <gtkmm/image.h>
#include <vector>
#include<algorithm>
#include <chrono>
#include <string.h>

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
 dificuldade(0),
 qtdARevelar(0)
  {


// inicia os elementos da biblioteca GTKmm para a contrução da janela

  set_default_size(1024,768);
  set_title("Campo minado Jardel e Micaelli");

  // inicializa os botoes e faz a ligação do sinal do click para as respectivas funçoes passando os argumentos
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

// função do click do botão do grid
void CampoMinado::on_clicked(int positionX,int positionY)
{
  
  Gtk::Widget* pWidgetSelecionado =  gridJogo.get_child_at(positionX,positionY);
  Gtk::Button* pBtSelecionado = dynamic_cast<Gtk::Button*>(pWidgetSelecionado); 
  if(!(*pBtSelecionado).get_always_show_image()){


     // se a celula selecionada for bomba
      if(vetor[positionX][positionY]==-1){

          for(int i=0;i<vetor.size();i++){
              std::vector<int> linha = vetor[i];
              for(int j=0;j<linha.size();j++){
                Gtk::Widget* pWidget =  gridJogo.get_child_at(i,j);
                Gtk::Button* pBt = dynamic_cast<Gtk::Button*>(pWidget); 
                (*pBt).set_always_show_image(true);
          	}	
         }

         fim = std::chrono::system_clock::now();
         calcularTempo();
        // aqui apresenta o fim do jogo
        Gtk::MessageDialog dialogFimDoJogo(*this, "Fim do jogo!");
        dialogFimDoJogo.set_secondary_text("Para jogar novamento clique no botão \"NovoJogo\"\n\nO seu tempo foi: "+std::to_string(duracao.count())+" segundos");
        dialogFimDoJogo.run();
         
      }else{
        (*pBtSelecionado).set_always_show_image(true);
            
            qtdARevelar--;

            std::vector<int> li = vetor[positionX];


            for(int x=positionX-1;x<positionX+2;x++){
              for(int y=positionY-1;y<positionY+2;y++){
                if(x>=0 && x<vetor.size() && y>=0 && y<li.size()){
                       if(vetor[x][y]!=-1){
                    Gtk::Widget* pWidget =  gridJogo.get_child_at(x,y);
                    Gtk::Button* pBt = dynamic_cast<Gtk::Button*>(pWidget); 
                    if(!(*pBt).get_always_show_image()){
                        qtdARevelar--;
                        (*pBt).set_always_show_image(true);
                    }
                    

                  }


                }


              }


        }

         // aqui verifica se ainda tem celula a ser revelada para determinar o fim do jogo caso haja vencedor
           if(qtdARevelar==0){

                for(int i=0;i<vetor.size();i++){
                    std::vector<int> linha = vetor[i];
                    for(int j=0;j<linha.size();j++){
                      Gtk::Widget* pWidget =  gridJogo.get_child_at(i,j);
                      Gtk::Button* pBt = dynamic_cast<Gtk::Button*>(pWidget); 

                      (*pBt).set_always_show_image(true);


                  }	
              }

              fim = std::chrono::system_clock::now();
              calcularTempo();
              // aqui apresenta o fim do jogo
              Gtk::MessageDialog dialogFimDoJogo(*this, "Parabéns!");
              dialogFimDoJogo.set_secondary_text("Você ganhou o jogo!\n\nO seu tempo foi: "+std::to_string(duracao.count())+" segundos");
              dialogFimDoJogo.run();

           }

          

      
      }
      

  }
   

}


// função que inicia o jogo
void CampoMinado::on_iniciarJogo(int dif)
{
  
  qtdARevelar=0;
  inicio = std::chrono::system_clock::now();


// pega qual nivel está selecionado
 if(avancado.get_active()){
   dificuldade=2;
 }else if(intermediario.get_active()){
   dificuldade=1;
 }else{
   dificuldade=0;
 }

// apaga todas as linhas do grid de acordo com o vetor


    for(int i=10;i>0;i--){
        gridJogo.remove_row(i-1);	
        
	    }


  // apaga todos os elementos do vetor 
  if(vetor.size()>0){
    vetor.clear();
  }
 

// aqui chama a função de iniciar a matrix de acordo com o nivel de dificuldade selecionado
 switch (dificuldade)
 {

 case 0:
    gerar_mapa(vetor,10,10,10);

   break;
     
   case 1:

     gerar_mapa(vetor,15,15,40);
   break;

   case 2:
      gerar_mapa(vetor,15,30,100);
   break;
 
 default:

    gerar_mapa(vetor,10,10,10);

   break;

 }


// aqui preenche o grid da interface grafica colocando um botão dentro de cada celula do grid espelando a matrix do vetor
// cada botão é adicionado em tempo de execução e é definido a função que vai ser chamada no evendo click e a sua posição como argumendo 
  for(int i=0;i<vetor.size();i++){
    std::vector<int> linha = vetor[i];
		for(int j=0;j<linha.size();j++){
			Gtk::Button* pButton = new Gtk::Button("",false);
      (*pButton).signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,&CampoMinado::on_clicked), i,j));
		  Gtk::Image* icon = new Gtk::Image;
      
      // aqui coloca as imagens nos botoes
      switch (linha[j])
      {
      case -1:
        icon->set("bomba.png");
        // marcar bombas para testar vitoria
      //  (*pButton).set_label("b");
        break;
       case 0:
            icon->set("trevo.png");
            qtdARevelar++;
        break;
       case 1:
          icon->set("1.png");
          qtdARevelar++;
        break; 
        case 2:
          icon->set("2.png");
          qtdARevelar++;
        break;
        case 3:
          icon->set("3.png");
          qtdARevelar++;
        break;
        case 4:
          icon->set("4.png");
          qtdARevelar++;
        break;
        case 5:
          icon->set("5.png");
          qtdARevelar++;
        break;
        case 6:
          icon->set("6.png");
          qtdARevelar++;
        break;
        case 7:
          icon->set("7.png");
          qtdARevelar++;
        break;
        case 8:
          icon->set("8.png");
          qtdARevelar++;
        break;
      default:

        break;
      }
      
       
      (*pButton).set_image(*Gtk::manage(icon));
      // revelar ou nao a imagem do botao
      (*pButton).set_always_show_image(false);
      // adiciona o botao no grid
      gridJogo.attach(*pButton,i,j,1,1);
		}		
	}




 

 show_all_children();


}


void CampoMinado::on_defineNivel(int dif)
{
  //dificuldade=dif;
}

// funcão chamada pelo botão de ajuda e que exibe uma janela com as regras do jogo.
void CampoMinado::on_clickedAjuda(int a)
{

Gtk::MessageDialog dialog(*this, "Informações sobre o jojo");
  dialog.set_secondary_text(" O jogo consiste em uma área matricial de n linhas por m colunas com um total de n * m células e k minas. Inicialmente, as células estão ocultas, ou seja, não é possível determinar se ela possui uma mina ou não, e o objetivo do jogo é revelar todas as células que não possuem minas. Assim, uma célula pode ser revelada por uma ação do usuário ou por uma das regras do jogo e isso pode resultar em uma das três situações possíveis:\n\n1 - Uma mina é revelada:\n Nesse caso, o jogo encerra com a derrota do usuário; \n\n2 - Um número é revelado: \n O valor indica a quantidade de minas adjacentes, isto é, a quantidade de minas nas 8 células vizinhas; \n\n3 - Uma posição vazia é revelada:\n nesse caso, o jogo revela automaticamente todas as células adjacentes a essa posição, visto que ela não possui minas adjacentes.\n\n  O usuário vence o jogo ao revelar todas as células que não contêm minas. Além disso, o usuário pode marcar uma célula não revelada com uma bandeira caso ele acredite que não existe uma mina nessa posição. Logo, o usuário pode aplicar a ação revelar sobre um número desde que a quantidade de bandeiras adjacentes seja igual ao seu número. Assim, todas as células adjacentes, que não estão marcadas por bandeiras, são reveladas automaticamente. Observe, que isso ocorrerá mesmo que as bandeiras estejam posicionadas incorretamente e assim revelando uma mina.Por fim, a dificuldade do jogo irá determinar as dimensões da área do jogo, a quantidade de minas e se a primeira ação revelar sempre será um número ou sempre será uma posição vazia.");
  dialog.run();
  
}


// função chamada pelo botao sair e que finaliza a aplicação
void CampoMinado::on_clickedClose(int r)
{
   close();
}


// função que preenche o mapa do vetor e que coloca as bombas para depois ser exibido no grid do componente grafico
void CampoMinado::preencher(std::vector<std::vector<int>> & vet, int linhas, int colunas, int bombas){

  unsigned seed =time(0);
  srand(seed);
   
  for (int quantidade=0; quantidade<bombas; quantidade++){
      
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

}
   

// inicializa a matrix (vector) com o tamanho passado como parametros
void CampoMinado::gerar_mapa(std::vector<std::vector<int>> & vet, int linhas, int colunas, int bomba){ //inicializa o mapa com valores zeros
  
  for(int y=0;y<linhas;y++){
    // vetor que representa uma linha
    std::vector<int> linha;
    for(int x=0;x<colunas;x++){
      linha.push_back(0);
    }
    vet.push_back(linha);
  }
   
 
  preencher( vet, linhas, colunas, bomba);
 
}


// função que calcula o tempo decorrido do jogo em segundos
// essa função é chamada no fim do jogo utilizando as variaveis de tempo atribuidas no inicio e no fim do jogo
void CampoMinado::calcularTempo() {
  duracao = fim - inicio;
}



/*
bool record_cmp(Record &a, Record &b) {
  return a.milliseconds < b.milliseconds;
}

void sort122(std::vector<Record> &records) {
  for(int k=0;k<records.size();k++){
    int pos = 0;
    for(int i=k+1;i<records.size();i++){
      if(record_cmp(records[i], records[pos])){
        pos = i;
      }
    }
    Record tmp = records[pos];
    records[pos] = records[k];
    records[k] = tmp;
  }
}
*/