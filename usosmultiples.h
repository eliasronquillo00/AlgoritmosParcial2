/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/cFiles/file.h to edit this template
 */

/* 
 * File:   usosmultiples.h
 * Author: eliasr04
 *
 * Created on 24 de mayo de 2024, 14:00
 */

#ifndef USOSMULTIPLES_H
#define USOSMULTIPLES_H

#ifdef __cplusplus
extern "C" {
#endif
/**
* Se encarga de inicializar (si es necesario) su invocacion
* esta llamada se realizara una sola vez al inicio de la ejecucion
*/
void inicializar_usosmultiples(void);
/**
* Dibuja su entrega de multiusos
*/
void dibujar_usosmultiples();

/**
* retorne su numero de carnet en la invocacion, en base a esto se asignara su nota de forma automatica
*/
const char* get_carnet(void);



#ifdef __cplusplus
}
#endif

#endif /* USOSMULTIPLES_H */

