#ifndef AMOBA_HPP
#define AMOBA_HPP

#include "application.hpp"
#include "gamemaster.hpp"
#include <vector>


/*
=========== LEÍRÁS ===========
Amõba játék megvalósítása:
- GUI: kirajzolást az 'Amoba' class végzi, ami egy 'Application' leszármazott.
- Játék: a játékszabályokat a 'GameMaster' singleton class vezérli, ami 'Amoba' mezõjeként szerepel.

Player1 jele X, Player2 jele O.
Az nyer, aki először rak le a saját szimbólumából 5 darabot egymás mellé sorban, oszlopban vagy átlósan.
Ha betelik a pálya, és senki nem nyert az utolsó lépésben sem, akkor döntetlen a játék.

Lehet játszani gépi játékos ellen is, ez a főmenüben állítható.
Szintén állítható a pálya mérete, 15x15 és 30x30 között.

==============================
*/

enum State
{
    st_mainmenu,
    st_gameinit,
    st_ingame,
    st_gameover
};

class Amoba : public Application
{
public:
    Amoba();
    virtual ~Amoba();

    virtual void action(genv::event);

    void update_grid();
    void game_over(char);
    void change_state_to(State);
    void btn_handler(std::string);


protected:
    // ============= GAME VARIABLES ==============

    // ------ Rules ------
    GameMaster *_gamemaster;

    // ------ State ------
    State _state;


    // ========== GUI ELEMENTS (WIDGETS) =========

    // ------ Interactive Menu Gui Elements ------
    // option selector widgets
    Dropdown *_gamemode_dropdown;
    Spinbox *_size_spinbox;

    // menu buttons
    Button  *_btn_start,         // main menu, new game
            *_btn_restart,       // game over menu, new game
            *_btn_backtomenu;    // game over menu, go back to main menu

    // game-specific tiling widget
    AmobaGrid *_grid;

    // ------ Static Gui Elements ------
    // text elements
    StaticText *_title_label,    // main menu, game title
               *_size_label,     // main menu, label above '_size_spinbox'
               *_gamemode_label, // main menu, label above '_gamemode_dropdown'
               *_options_label,  // main menu, label above selector widgets
               *_popup_label; // game over menu, label in popup window

    // background stuff
    Rect2 *_popup_window;  // game over popup window

    std::vector<genv::color> _bg_color_list;
};

#endif // AMOBA_HPP
