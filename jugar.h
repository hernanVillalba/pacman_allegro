#ifndef JUGAR_H_INCLUDED
#define JUGAR_H_INCLUDED

void jugar(){
    int v=3;
    puntaje=0;
    Puntuacion oPuntuacion;

    while (v>-1){
    play_midi(sountrack_stage_1,300);
    bool game_over = false;
    bool primera_vez = false;
    Pacman oPacman(v);

    oPuntuacion.leerDeArchivo();
    oPuntuacion.solordenarScores();
    Mapa oMapa;
    Fantasma oGhost1(TAM*12,TAM*11,0);
    Fantasma oGhost2(TAM*13,TAM*11,1);
    Fantasma oGhost3(TAM*14,TAM*11,2);
    Fantasma oGhost4(TAM*15,TAM*11,3);
    Fantasma oGhost5(TAM*16,TAM*11,4);


    int ghost_x,ghost_y;
    bool o=true;
    while(!game_over){


        if(!primera_vez){
            //para pausar la pantalla al comienzo
            pantalla_princio(&primera_vez,oMapa,oPacman);
        }
        if(key[KEY_ESC] || oPacman.getVidas()== -1 || oPacman.escapePacman()){ //si no hay comida... termina el juego
            game_over = true;
        }
        if(key[KEY_ESC]){
            oPacman.setVidas(-3);
        }

        if(key[KEY_P]){
            allegro_message("Pausa! :)\n Pero ambos sabemos que el Pacman original no la tenia \n Presione 'aceptar' para volver al juego.");

        }

        if (oGhost1.choqueFantasma(oPacman)){
            stop_midi();
            oPacman.DibujarMuerte(oMapa);
            oPacman.restarVida();
            oPacman.posicionInicial();
            oGhost1.posicionInicialGhost();
            oGhost2.posicionInicialGhost();
            oGhost3.posicionInicialGhost();
            oGhost4.posicionInicialGhost();
            oGhost5.posicionInicialGhost();
            play_midi(sountrack_stage_1,300);
            //mensaje de ready ///////////////////
            if (oPacman.getVidas()>-1){
            draw_sprite(screen,ready,11*TAM,6*TAM);
            rest(5000);}
            else break;
        }

        if (oGhost2.choqueFantasma(oPacman)){
            stop_midi();
            oPacman.DibujarMuerte(oMapa);
            oPacman.restarVida();
            oPacman.posicionInicial();
            oGhost1.posicionInicialGhost();
            oGhost2.posicionInicialGhost();
            oGhost3.posicionInicialGhost();
            oGhost4.posicionInicialGhost();
            oGhost5.posicionInicialGhost();
            play_midi(sountrack_stage_1,300);
            //mensaje de ready ///////////////////
            if (oPacman.getVidas()>-1){
            draw_sprite(screen,ready,11*TAM,6*TAM);
            rest(5000);} else break;
        }
        if (oGhost3.choqueFantasma(oPacman)){
            stop_midi();
            oPacman.DibujarMuerte(oMapa);
            oPacman.restarVida();
            oPacman.posicionInicial();
            oGhost1.posicionInicialGhost();
            oGhost2.posicionInicialGhost();
            oGhost3.posicionInicialGhost();
            oGhost4.posicionInicialGhost();
            oGhost5.posicionInicialGhost();
            play_midi(sountrack_stage_1,300);
            //mensaje de ready ///////////////////
            if (oPacman.getVidas()>-1){
            draw_sprite(screen,ready,11*TAM,6*TAM);
            rest(5000);} else break;
        }
        if (oGhost4.choqueFantasma(oPacman)){
            stop_midi();
            oPacman.DibujarMuerte(oMapa);
            oPacman.restarVida();
            oPacman.posicionInicial();
            oGhost1.posicionInicialGhost();
            oGhost2.posicionInicialGhost();
            oGhost3.posicionInicialGhost();
            oGhost4.posicionInicialGhost();
            oGhost5.posicionInicialGhost();
            play_midi(sountrack_stage_1,300);
            //mensaje de ready ///////////////////
            if (oPacman.getVidas()>-1){
            draw_sprite(screen,ready,11*TAM,6*TAM);
            rest(5000);} else break;
        }
        if (oGhost5.choqueFantasma(oPacman)){
            stop_midi();
            oPacman.DibujarMuerte(oMapa);
            oPacman.restarVida();
            oPacman.posicionInicial();
            oGhost1.posicionInicialGhost();
            oGhost2.posicionInicialGhost();
            oGhost3.posicionInicialGhost();
            oGhost4.posicionInicialGhost();
            oGhost5.posicionInicialGhost();
            play_midi(sountrack_stage_1,300);
            //mensaje de ready ///////////////////
          if (oPacman.getVidas()>-1){
            draw_sprite(screen,ready,11*TAM,6*TAM);
            rest(5000);} else break;
        }


        dibujar_vidas_pacman(oPacman.getVidas());
        dibujar_puntaje(puntaje);
        oPuntuacion.maxPunt(vec_punt[0]);

//        se_presiono_una_tecla(oMapa);
        oPacman.moverPacman();

        if(oPacman.comidaGrande()){
        oGhost1.cambiarEstado();
        oGhost2.cambiarEstado();
        oGhost3.cambiarEstado();
        oGhost4.cambiarEstado();
        oGhost5.cambiarEstado();
        }

        oGhost1.moverFantasma();
        oGhost2.moverFantasma();
        oGhost3.moverFantasma();
        oGhost4.moverFantasma();
        oGhost5.moverFantasma();

//      imprime el pacman con la boca abierta
        clear(buffer);
        oPacman.Comer();
        oPacman.imprimirPacmanComiendo();

        oGhost1.dibujarFantasma();
        oGhost2.dibujarFantasma();
        oGhost3.dibujarFantasma();
        oGhost4.dibujarFantasma();
        oGhost5.dibujarFantasma();


        oPacman.imprimirMapa();

        rest(50);


        //imprime el pacman con la boca cerrada
        clear(pacman);
        oPacman.imprimirPacmanQuieto();
        oPacman.imprimirMapa();
        rest(50);
        oPacman.imprimirMapa();
        if(!oPacman.hayComida()){
            oPacman.puerta();
            if(o){
            oGhost1.posicionInicialGhost();
            oGhost2.posicionInicialGhost();
            oGhost3.posicionInicialGhost();
            oGhost4.posicionInicialGhost();
            oGhost5.posicionInicialGhost();
            o=false;}

        }

    }

    v=oPacman.getVidas();
    stop_midi();

}

if(puntaje>vec_punt[3])
    {clear(buffer);
    oPuntuacion.cargarNewscore(puntaje);}

}

#endif // JUGAR_H_INCLUDED
