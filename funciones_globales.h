#ifndef FUNCIONES_GLOBALES_H_INCLUDED
#define FUNCIONES_GLOBALES_H_INCLUDED
#include "mapa.h"

void iniciar_allegro(){
    allegro_init();
    install_keyboard();
    set_color_depth(32);
    set_gfx_mode(GFX_AUTODETECT_WINDOWED,1200,640,0,0);
    buffer = create_bitmap(1200,640);

    //cargar la imagen
    bloque = load_bitmap("images/mapa/mapa_bloque.bmp",NULL);
    comida = load_bitmap("images/mapa/mapa_comida.bmp",NULL);
    pacBMP = load_bitmap("images/pacman/pacman.bmp",NULL);
    pacman = create_bitmap(TAM,TAM);
    portal_IZQ = load_bitmap("images/mapa/mapa_portal_izq.bmp",NULL);
    portal_DER = load_bitmap("images/mapa/mapa_portal_der.bmp",NULL);
    inicio = load_bitmap("images/menu/inicio.bmp",NULL);
    cursor = load_bitmap("images/menu/cursor.bmp",NULL);
}
//pone el bitmap en el inicio
void poner_inicio()
{
    blit(buffer,screen,0,0,0,0,1200,640);
    blit(inicio,buffer,0,0,0,0,1200,640);

   }
//movimiento del cursor
void mover_cursor()
{
    if (key[KEY_UP] && cy>256)  {cy-=TAM*3;}
    else if (key[KEY_DOWN] && cy<544)  {cy+=TAM*3;}
    rest(100);
    clear_keybuf();
    }
//impresion de la pantalla y funcionalidad
void pantalla_inicial()
{   bool continuar=true;
    while (continuar)
    {
    poner_inicio();
    draw_sprite (buffer,cursor,cx,cy);
    mover_cursor();
    //pantalla();
    if (key[KEY_ENTER]) continuar= false;}
}

void se_presiono_una_tecla(){
    // detecta la tecla que se precin� para asignarle el numero correspondiente a la direcci�n
    if(key[KEY_RIGHT] || key[KEY_D]) dir = 0; //DER vale 0
    else if(key[KEY_UP] || key[KEY_W]) dir = 1; //ARRIB vale 1
    else if(key[KEY_LEFT] || key[KEY_A]) dir = 2; //IZQ vale 2
    else if(key[KEY_DOWN] || key[KEY_S]) dir = 3; //ABAJ vale 3
}

int inicia_audio(int izquierda, int derecha){
    if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0) {
       allegro_message("Error: inicializando sistema de sonido\n%s\n", allegro_error);
       return 1;
    }

	set_volume(izquierda, derecha);
    return 0;
}

void mover_pacman(Mapa oMapa){
    if(dir == 0 && oMapa.bordeMapa()) px += TAM;
    if(dir == 1 && oMapa.bordeMapa()) py -= TAM;
    if(dir == 2 && oMapa.bordeMapa()) px -= TAM;
    if(dir == 3 && oMapa.bordeMapa()) py += TAM;
}

#endif // FUNCIONES_GLOBALES_H_INCLUDED
