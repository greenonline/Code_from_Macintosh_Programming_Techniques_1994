/*+++++++++++++++++++++ Include Files I I I I I I I I II+++++++++*/
//#include (Sound.h)
#include "Sound.h"
/*+++++++++++++++++ Function prototypes +++++++++++++++++*/
void Get_Some_Strings( void);
void Draw_Moving_Picture( void);
void Play_A_Sound( short);
/*++++++++++++ Define global constants ++++++++++++++++++*/
#define IN_FRONT (WindowPtr) -1L

#define NIL 0L
#define WIND_ID 128


#define REMOVE_EVENTS 0
#define STR_LIST_ID 128
#define WIND_TITLE_STR 1
#define PICT_LABEL_STR 2
#define PICT_LABEL_STR_L 70
#define PICT_LABEL_STR_B 140
#define FIRST_MAN_PICT 128
#define PICT_L 70
#define PICT_T 10
#define DELAY_TICKS 7
#define SND_GLASS_ID 9000
#define SND_ELVIS_ID 9001
#define SND_CLINT_ID 9002

/*++++++++++++++ Define global variables ++++++++++++++++*/

WindowPtr The_Window;
Boolean All_Done = FALSE;
EventRecord The_Event;

GrafPtr thePort;  //added mgj
/*++++++++++++++++++++ main listing +++++++++++++++++++++++*/
void main( void ) {
  InitGraf ( &thePort ) ;
  InitFonts () ;
  InitWindows();
  InitMenus();
  TEInit();
  InitDialogs( NIL);
  FlushEvents( everyEvent, REMOVE_EVENTS );
  InitCursor () ;
  The_Window = GetNewWindow( WIND_ID, NIL, IN_FRONT );
  if ( The_Window == NIL)
    ExitToShell () ;
  SetPort( The_Window ); 


  Get_Some_Strings();
  Draw_Moving_Picture();
  Play_A_Sound( SND_GLASS_ID ) ;
  Play_A_Sound( SND_ELVIS_ID );
  Play_A_Sound( SND_CLINT_ID );
  while ( All_Done == FALSE )
  {
    GetNextEvent( everyEvent, &The_Event ) ;
    switch ( The_Event.what)
    {
      case mouseDown:
        All_Done = TRUE;
        break;
    }
  }
}

/*++++++++++++ Get strings from 'STR#' resource +++++++++++*/
void Get_Some_Strings( void )
{
  Str255 the_str;
  SetPort( The_Window );
  GetIndString( the_str, STR_LIST_ID, WIND_TITLE_STR );
  SetWTitle( The_Window, the_str );
  GetIndString( the_str, STR_LIST_ID, PICT_LABEL_STR );
  MoveTo( PICT_LABEL_STR_L, PICT_LABEL_STR_B );
  DrawString( the_str );
}



/*+++1111 I I I I I Create animation using 'PICT's ++I II I II I I I I I*/
void Draw_Moving_Picture( void )
{
  Rect pict_rect;
  PicHandle pict_handle;

  short pict_wd;
  short pict_ht;
  short i;
  short count;
  short pict_id;
  long end_tick;
  SetPort( The_Window );
  pict_handle = GetPicture( FIRST_MAN_PICT );
  pict_rect = ( **( pict_handle) ).picFrame;
  pict_wd = pict_rect.right - pict_rect.left;
  pict_ht = pict_rect.bottom - pict_rect.top;


  SetRect(&pict_rect, PICT_L, PICT_T, PICT_L + pict_wd, PICT_T + pict_ht);
  count= 0;
  for ( i=1; i < 31; i++)
  {
     ++count;
     switch (count )
     {
       case 1:
         pict_id =FIRST_MAN_PICT;
         break;
       case 2:
         pict_id =FIRST_MAN_PICT + 1;
         break;
       case 6:
         pict_id = FIRST_MAN_PICT + 1;
         count = 0;
         break;
       case 3:
       case 5:
         pict_id = FIRST_MAN_PICT + 2;
         break;
       case 4:
         pict_id = FIRST_MAN_PICT + 3;
         break;
    }   
    pict_handle = GetPicture( pict_id ) ;
    DrawPicture( pict_handle, &pict_rect );




    Delay( DELAY_TICKS, &end_tick );
  }
}

/*+++++++++ Play one sound from a 'snd ' resource +++++++++*/
void Play_A_Sound( short snd_id )
{
  Handle snd_handle;
  OSErr err;
  snd_handle = GetResource( 'snd ' , snd_id );
  if ( snd_handle == NIL )
    ExitToShell ();
  err= SndPlay( NIL, snd_handle, TRUE);
  if ( err != noErr )
    ExitToShell () ;

}


