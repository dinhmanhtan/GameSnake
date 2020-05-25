#include "Menu_Game.h"

void Menu_Game::Load_imgIcon(SDL_Renderer* render,const string & s,BaseObject &icon)
{
    if(!icon.LoadIMG(s.c_str(), render) )
        cout << "Error : Load image is failed . " << s << endl;
    SDL_QueryTexture(icon.GetObject(),NULL, NULL,&icon.rect_.w, &icon.rect_.h);
}

Menu_Game::Menu_Game(SDL_Renderer *render)
{
 // Initialize text

  text_menu[0].SetText("Play");
  text_menu[1].SetText("Exit") ;
  text_menu[2].SetText("New Play") ;
  text_menu[3].SetText("Continue") ;
  text_menu[4].SetText("2 Player") ;

  text_menu[0].SetRect(300,450);
  text_menu[1].SetRect(310,610);

  text_menu[2].SetRect(260,430);
  text_menu[3].SetRect(260,500);
  text_menu[4].SetRect(260,530) ;

  for(int i=0; i<5; i++)
    text_menu[i].draw = true;

  for(int i=0; i<itemMenu ; i++)
     text_menu[i].setText_Color(BLACK_COLOR) ;

 // Initialize icons

    Load_imgIcon( render,"Image/icon/iconp9.png",icon_pauseP2) ;


  // Load image menu P2

  Load_imgIcon(render,"Image/menu/resumeP1.png", resume[0]);
  Load_imgIcon(render,"Image/menu/resumeP.png", resume[1]);

  Load_imgIcon(render,"Image/menu/restartP1.png", restart[0]);
  Load_imgIcon( render,"Image/menu/restartP.png",restart[1]);
  Load_imgIcon(render,"Image/menu/homeP1.png", home[0]);
  Load_imgIcon(render,"Image/menu/homeP.png", home[1]);

  Load_imgIcon(render,"Image/menu/exitP1.png", exit[0]);
  Load_imgIcon(render,"Image/menu/exitP.png", exit[1]);

  Load_imgIcon(render, "Image/menu/iconResume1.png",icon_resumeP2[0] );
  Load_imgIcon(render, "Image/menu/iconResume.png",icon_resumeP2[1] );

  Load_imgIcon(render, "Image/menu/iconRestart1.png",icon_restartP2[0] );
  Load_imgIcon(render, "Image/menu/iconRestart.png",icon_restartP2[1] );

  Load_imgIcon(render, "Image/menu/iconHome1.png",icon_homeP2[0] );
  Load_imgIcon(render, "Image/menu/iconHome.png",icon_homeP2[1] );

  Load_imgIcon(render, "Image/menu/iconExit1.png",icon_exitP2[0] );
  Load_imgIcon(render, "Image/menu/iconExit.png",icon_exitP2[1] );

  for(int i=0 ; i<2; i++)
   {
     resume[i].draw = !i;
     restart[i].draw = !i;
     home[i].draw = !i;
     exit[i].draw = !i;

     icon_resumeP2[i].draw = !i;
     icon_restartP2[i].draw = !i;
     icon_homeP2[i].draw = !i;
     icon_exitP2[i].draw = !i;

   }


   set_iconP2();
}

void Menu_Game::set_iconP2()
{

    icon_pauseP2.SetSize(Size2+15,Size2+15) ;
    icon_pauseP2.SetRect(14*Size2+7,Size2*3);
    SDL_SetTextureColorMod(icon_pauseP2.GetObject(), 255,0,255) ;


//
    for(int i=0; i<2; i++){
      resume[i].SetRect(270,150);
      restart[i].SetRect(270,250);
      home[i].SetRect(270,350);
      exit[i].SetRect(270,450);

      icon_restartP2[i].SetRect(190,250);
      icon_resumeP2[i].SetRect(190,150);
      icon_homeP2[i].SetRect(190,350);
      icon_exitP2[i].SetRect(190,450) ;
    }


}



void Menu_Game::Handle_event(SDL_Event m_event , bool &running ,bool &Call_menu,bool &play1,
                             Snake &s, bool &player_2, Player2& p2, float &time_over, bool &pauseP1)
{

      for(int i=0; i<5; i++)  {
        if(Call_menu == true )
         text_menu[i].draw = true;
        else
         text_menu[i].draw = false;
      }


      switch (m_event.type) {

           case SDL_QUIT :
                running = false;
           case SDL_MOUSEMOTION :
              {
                xMouse = m_event.motion.x;
                yMouse = m_event.motion.y ;

               for(int i=0; i<itemMenu; i++)
                {
                   if(CheckFocusWithRect(xMouse,yMouse,text_menu[i].GetRect())  )
                       text_menu[i].setText_Color(RED_COLOR);

                    else text_menu[i].setText_Color(BLACK_COLOR);

                }

                 break;
               }

             case SDL_MOUSEBUTTONDOWN :
             {
                 if( !play1) {

                     if(CheckFocusWithRect(xMouse,yMouse,text_menu[0].GetRect()) && text_menu[0].draw) {
                         Call_menu = false;
                         play1 = true;
                         player_2 = false;


                       }
                     if(CheckFocusWithRect(xMouse,yMouse,text_menu[4].GetRect()) && text_menu[4].draw) {
                             player_2 = true;
                             Call_menu = false;

                       }

                 }else {

                     if(CheckFocusWithRect(xMouse,yMouse,text_menu[2].GetRect()) && text_menu[2].draw) {
                           s.Reset_game();
                           time_over = 0.f;
                           Call_menu = false;
                           pauseP1   = false;

                      } else if(CheckFocusWithRect(xMouse,yMouse,text_menu[3].GetRect()) && text_menu[3].draw) {

                             play1     = true;
                             Call_menu = false;
                             player_2  = false;
                      }

                      if(CheckFocusWithRect(xMouse,yMouse,text_menu[4].GetRect()) && text_menu[4].draw) {
                             p2.set_up();
                             player_2  = true;
                             Call_menu = false;

                       }

                }

                if(CheckFocusWithRect(xMouse,yMouse,text_menu[1].GetRect()) && text_menu[4].draw)
                             running = false;


                 break;

            }

        }


}

void Menu_Game::Draw_Menu(SDL_Renderer *render ,TTF_Font *font,const bool &play1  )
{
     if(!play1) {


       for(int i=0; i< 2; i++) {
        text_menu[i].CreateGameText(font, render);
        text_menu[i].DrawText(render);
       }
        text_menu[4].CreateGameText(font, render);
        text_menu[4].DrawText(render);

    } else {
        text_menu[4].SetRect(260,570);
        text_menu[1].SetRect(310,650);

      for(int i=1; i<itemMenu ; i++) {
         text_menu[i].CreateGameText(font, render);
         text_menu[i].DrawText(render);
        }
     }
}


void Menu_Game::Draw_menuP2(SDL_Renderer *render, bool &pauseP2)
{


   for(int i=0; i<2; i++)
   {
      if(resume[i].draw)
         resume[i].Render(render);

      if(restart[i].draw)
         restart[i].Render(render);

      if(home[i].draw)
         home[i].Render(render);

      if(exit[i].draw)
         exit[i].Render(render);

      if(icon_restartP2[i].draw)
         icon_restartP2[i].Render(render);

      if(icon_resumeP2[i].draw)
         icon_resumeP2[i].Render(render);

      if(icon_homeP2[i].draw)
         icon_homeP2[i].Render(render);

      if(icon_exitP2[i].draw)
         icon_exitP2[i].Render(render) ;


  }

}

void Menu_Game::Check_menuP2(Player2 &p2, SDL_Event  g_event, bool &pauseP2,
                            bool &running, bool &call_menu, bool& play_2, bool &play1)
{

   if(g_event.type == SDL_MOUSEBUTTONDOWN ) {
      if(pauseP2 == false) {

         if(CheckFocusWithRect(xMouse,yMouse,icon_pauseP2.rect_) )
             pauseP2 = true;

      } else {


          if(CheckFocusWithRect(xMouse,yMouse,resume[1].rect_ ) && resume[1].draw) {

                   pauseP2 = false;

          }else if(CheckFocusWithRect(xMouse,yMouse,restart[1].rect_ ) && restart[1].draw ) {

                   pauseP2 = false;
                   p2.set_up();

          }else if(CheckFocusWithRect(xMouse,yMouse,home[1].rect_) && home[1].draw ) {

                   p2.set_up();
                   pauseP2 = false;
                   play_2 = false;
                   call_menu = true;

          }else if(CheckFocusWithRect(xMouse,yMouse,exit[1].rect_) && exit[1].draw ) {
                   running = false;

          }

      }
   }

    if(CheckFocusWithRect(xMouse,yMouse,resume[0].rect_) ) {
        resume[0].draw = false;
        resume[1].draw = true;
        icon_resumeP2[0].draw = false;
        icon_resumeP2[1].draw = true;

    } else {
        resume[0].draw = true;
        resume[1].draw = false;
        icon_resumeP2[0].draw = true;
        icon_resumeP2[1].draw = false;
    }

    if(CheckFocusWithRect(xMouse,yMouse,restart[0].rect_) ) {
        restart[0].draw = false;
        restart[1].draw = true;
        icon_restartP2[0].draw = false;
        icon_restartP2[1].draw = true;

    } else {
        restart[0].draw = true;
        restart[1].draw = false;
        icon_restartP2[0].draw = true;
        icon_restartP2[1].draw = false;

    }

    if(CheckFocusWithRect(xMouse,yMouse,home[0].rect_) ) {
        home[0].draw = false;
        home[1].draw = true;
        icon_homeP2[0].draw = false;
        icon_homeP2[1].draw = true;


    } else {
        home[0].draw = true;
        home[1].draw = false;
        icon_homeP2[0].draw = true;
        icon_homeP2[1].draw = false;
    }

    if(CheckFocusWithRect(xMouse,yMouse,exit[0].rect_) ) {
        exit[0].draw = false;
        exit[1].draw = true;
        icon_exitP2[0].draw = false;
        icon_exitP2[1].draw = true;

    } else {
        exit[0].draw = true;
        exit[1].draw = false;
        icon_exitP2[0].draw = true;
        icon_exitP2[1].draw = false;
    }


   if(CheckFocusWithRect(xMouse,yMouse,icon_pauseP2.rect_) ) {
         icon_pauseP2.SetSize(Size2+30,Size2+30) ;


     } else {
       icon_pauseP2.SetSize(Size2+15,Size2+15) ;


    }

}

Menu_Game::~Menu_Game()
{
    icon_pauseP2.Free();

    for(int i=0; i<2 ; i++) {

      resume[i].Free();
      restart[i].Free();
      home[i].Free();
      exit[i].Free() ;

    }

    for(int i=0; i<itemMenu; i++)
      text_menu[i].~TextObject();


}
