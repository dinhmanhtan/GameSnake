#ifndef MENU_GAME_H
#define MENU_GAME_H

#include "Player2.h"


class Menu_Game
{
  public :
      Menu_Game(SDL_Renderer *render);
      ~Menu_Game();

      void Load_imgIcon(SDL_Renderer* render,const string & s,BaseObject &icon);

      void Draw_Menu(SDL_Renderer *render, TTF_Font *font, const bool &play1) ;

      void Handle_event(SDL_Event m_event, bool &running , bool &Call_menu,bool &play1,
            Snake &s, bool &player_2,  Player2& p2, float &time_over, bool &pauseP1) ;

      void set_iconP2();

      void Draw_menuP2(SDL_Renderer *render,bool &pauseP2);

      void Check_menuP2(Player2 &p2, SDL_Event  g_event, bool &pauseP2,
                       bool &running, bool &call_menu, bool& play_2, bool &play1);


  private :
    int itemMenu =5 ;

    TextObject text_menu[5];

    BaseObject resume[2];
    BaseObject restart[2];
    BaseObject exit[2];
    BaseObject home[2];

    BaseObject icon_resumeP2[2] , icon_restartP2[2];
    BaseObject icon_homeP2[2], icon_exitP2[2];

  public :

    BaseObject icon_pauseP2;
    int xMouse , yMouse ;

};




#endif // MENU_GAME_H
