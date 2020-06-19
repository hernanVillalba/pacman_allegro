#ifndef FUNCIONES_GLOBALES_H_INCLUDED
#define FUNCIONES_GLOBALES_H_INCLUDED
#include "mapa.h"
#include "fantasmas.h"
#include "pacman.h"

//protoripos
void iniciar_sonido();

//funciones
void iniciar_allegro(){
    //inicia allegro junto con sus imagenes
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
    fantBMP = load_bitmap("images/pacman/fantas.bmp",NULL);
    fantas = create_bitmap(TAM,TAM);
    comida_grande = load_bitmap("images/mapa/mapa_comida_grande.bmp",NULL);
    vidas_pacmanBMP = load_bitmap("images/pacman/pacman_vidas.bmp",NULL);
    vidas_pacman = create_bitmap(TAM*3,TAM);
    letras_vidas=load_bitmap("images/menu/vidas.bmp",NULL);
    numeros=load_bitmap("images/menu/numeros.bmp",NULL);
    score=load_bitmap("images/menu/puntaje.bmp",NULL);
    maxscore=load_bitmap("images/menu/maxpuntaje.bmp",NULL);
    unidad=create_bitmap(TAM,TAM);
    decena=create_bitmap(TAM,TAM);
    centena=create_bitmap(TAM,TAM);
    milesima=create_bitmap(TAM,TAM);
    puntajemax=100; /////////////////////////////////////////WTF???? que hace esto aca?;

    //carga de los sonidos
    iniciar_sonido();
    sountrack_stage_1 = load_midi("sounds/Map/sountrack_game-stage_01.mid");
    big_food = load_wav("sounds/pacman/bigfood_sound_pacman.wav");
    bolitas = load_wav("sounds/pacman/wakawaka_pacman.wav");
    portal_sountrack = load_wav ("sounds/Map/the-portal-sound-effect.wav");

}
//pone el bitmap en el inicio
void poner_inicio(){
    blit(buffer,screen,0,0,0,0,1200,640);
    blit(inicio,buffer,0,0,0,0,960,640);

}

void mover_cursor(){
    //movimiento del cursor
    if (key[KEY_UP] && cy>256)  {cy-=TAM*3;}
    else if (key[KEY_DOWN] && cy<544)  {cy+=TAM*3;}
    rest(100);
    clear_keybuf();
}
//impresion de la pantalla y funcionalidad
void pantalla_inicial(){
    bool continuar=true;
    while (continuar){
        poner_inicio();
        draw_sprite (buffer,cursor,cx,cy);
        mover_cursor();
        //pantalla();
        if (key[KEY_ENTER] && cy==256) continuar= false;
    }
}

void se_presiono_una_tecla(Mapa oMapa){
    // detecta la tecla que se precin� para asignarle el numero correspondiente a la direcci�n

    //para que el pacman no se detenga si hay un borde 'X'
    //o sea, si el pacman avanza hacia la izquierda y preciona arriba y justo hay un borde, que se quede con la anterior direccion
    char der = oMapa.getbordeDer(posicion_pacman_x, posicion_pacman_y); //dir = 0
    char arri = oMapa.getbordeArri(posicion_pacman_x, posicion_pacman_y); //dir = 1
    char izq = oMapa.getbordeIzq(posicion_pacman_x, posicion_pacman_y); //dir = 2
    char aba = oMapa.getbordeAba(posicion_pacman_x, posicion_pacman_y); //dir = 3

    if((key[KEY_RIGHT] || key[KEY_D]) && der != 'X') dir = 0; //DER vale 0
    else if((key[KEY_UP] || key[KEY_W]) && arri != 'X') dir = 1; //ARRIB vale 1
    else if((key[KEY_LEFT] || key[KEY_A]) && izq != 'X') dir = 2; //IZQ vale 2
    else if((key[KEY_DOWN] || key[KEY_S]) && aba != 'X') dir = 3; //ABAJ vale 3
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
//    char der = oMapa.getbordeDer(px,py); //dir = 0
//    char arri = oMapa.getbordeArri(px,py); //dir = 1
//    char izq = oMapa.getbordeIzq(px,py); //dir = 2
//    char aba = oMapa.getbordeAba(px,py); //dir = 3
//
//    if(dir == 0 && der == 'X'){
//        anterior_dir_Pacman = dir;
//    }
//    if(dir == 1 && arri == 'X'){
//        anterior_dir_Pacman = dir;
//    }
//    if(dir == 2 && izq == 'X'){
//        anterior_dir_Pacman = dir;
//    }
//    if(dir == 3 && aba == 'X'){
//        anterior_dir_Pacman = dir;
//    }

    oMapa.portalMapa();

    if(dir == 0 && oMapa.bordeMapa1()) posicion_pacman_x += TAM;
    if(dir == 1 && oMapa.bordeMapa1()) posicion_pacman_y -= TAM;
    if(dir == 2 && oMapa.bordeMapa1()) posicion_pacman_x -= TAM;
    if(dir == 3 && oMapa.bordeMapa1()) posicion_pacman_y += TAM;
}

void destruir(){
    destroy_bitmap(buffer);
    destroy_bitmap(pacBMP);
    destroy_bitmap(pacman);
    destroy_bitmap(fantas);
    destroy_bitmap(fantBMP);
    destroy_bitmap(bloque);
    destroy_bitmap(comida);
    destroy_bitmap(portal_IZQ);
    destroy_bitmap(portal_DER);
    destroy_bitmap(inicio);
    destroy_bitmap(cursor);
    destroy_bitmap(vidas_pacman);
    destroy_bitmap(vidas_pacmanBMP);
    destroy_bitmap(numeros);
    destroy_bitmap(unidad);
    destroy_bitmap(decena);
    destroy_bitmap(centena);
    destroy_bitmap(milesima);
    destroy_bitmap(score);
    destroy_bitmap(letras_vidas);
}

void dibujar_vidas_pacman(int vid){
        blit(vidas_pacmanBMP,vidas_pacman,vid*TAM,0,0,0,TAM*3,TAM);
        draw_sprite(buffer,letras_vidas,30*TAM,14*TAM);
        draw_sprite(buffer,vidas_pacman,30*TAM,15*TAM);
//        blit(buffer,screen,0,0,0,0,1200,640);
}

void dibujar_puntaje(int puntaje){
int nunidad,ndecena,ncentena,nmilesima;
        //decomponemos el num
        if (puntaje>=9999) puntaje=9999;
        nmilesima=puntaje/1000;
        puntaje=puntaje%1000;
        ncentena=puntaje/100;
        puntaje=puntaje%100;
        ndecena=puntaje/10;
        puntaje=puntaje%10;
        nunidad=puntaje/1;

        //usamos la descomposicion para buscar el num
        blit(numeros,unidad,nunidad*TAM,0,0,0,TAM,TAM);
        blit(numeros,decena,ndecena*TAM,0,0,0,TAM,TAM);
        blit(numeros,centena,ncentena*TAM,0,0,0,TAM,TAM);
        blit(numeros,milesima,nmilesima*TAM,0,0,0,TAM,TAM);

        //imprimimos el num descompuesto
        draw_sprite(buffer,score,30*TAM,4*TAM);
        draw_sprite(buffer,milesima,31*TAM,5*TAM);
        draw_sprite(buffer,centena,32*TAM,5*TAM);
        draw_sprite(buffer,decena,33*TAM,5*TAM);
        draw_sprite(buffer,unidad,34*TAM,5*TAM);
        blit(buffer,screen,0,0,0,0,1200,640);



}

void pantalla_princio(bool *primera_vez,Mapa oMapa,Pacman oPacman){
    *primera_vez = true;
    clear(buffer);
    oMapa.planoMapa();
    oMapa.imprimirMapa();
    rest(5000);
}

void iniciar_sonido(){
     if (install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL) != 0) {
       allegro_message("Error: inicializando sistema de sonido\n%s\n", allegro_error);
       system("pause");
       return;
    }
    set_volume(150, 150);
}

#endif // FUNCIONES_GLOBALES_H_INCLUDED
