#ifndef CAMPO_MINADO_H
#define CAMPO_MINADO_H

#include <gtkmm/window.h>
#include <gtkmm/application.h>
#include <gtkmm/fixed.h>
#include <gtkmm/box.h>
#include <gtkmm/alignment.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>
#include <gtkmm/frame.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/grid.h>
#include <gtkmm/paned.h>
#include <gtkmm/radiobutton.h>
#include <gtkmm/separator.h>
#include <vector>
#include <chrono>

class CampoMinado : public Gtk::Window
{
    Gtk::Fixed fixed;
    Gtk::Box boxGeral,boxSuperior,boxJogo;
    Gtk::Button botaoNovoJogo,botaoAjuda,botaoSair;
    Gtk::RadioButton iniciante, intermediario, avancado;
    Gtk::Grid gridJogo;
    Gtk::Frame frame1,frame2;
    Gtk::Paned pane;
    Gtk::Separator separador;
    int dificuldade,qtdARevelar;
    std::chrono::time_point<std::chrono::system_clock> inicio, fim;
    std::chrono::duration<double> duracao;
    

    std::vector<std::vector<int>> vetor;
    


public:
    CampoMinado(/* args */);
   // ~CampoMinado();
    
    protected:
        void on_clicked(int positionX,int positionY);
        void on_clickedAjuda(int a);
        void on_clickedClose(int r);
        void on_iniciarJogo(int dificuldade);
        void on_defineNivel(int dificuldade);
        void preencher(std::vector<std::vector<int>> & vet, int linhas, int colunas, int bombas);
        void gerar_mapa(std::vector<std::vector<int>> & vet, int linhas, int colunas, int bomba);
        void calcularTempo();

    
};



enum difficulty :int { BEGINNER=0, INTERMEDIARY=1, ADVANCED=2 };

#endif


