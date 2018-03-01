/*-------------------------------------------------------------------
**
**  Fichero:
**    button.c
**
**    Estructura de Computadores
**    Dpto. de Arquitectura de Computadores y Autom�tica
**    Facultad de Inform�tica. Universidad Complutense de Madrid
**
**  Prop�sito:
**    Contiene las implementaciones de las funciones
**    para la gesti�n de los pulsadores de la placa de prototipado
**
**  Notas de dise�o:
**
**-----------------------------------------------------------------*/

#include "44b.h"
#include "utils.h"
#include "button.h"
#include "leds.h"
#include "gpio.h"

unsigned int read_button(void)
{
	unsigned int buttons = 0;
	enum digital val;
	//COMPLETAR utilizando el interfaz del puerto G de gpio.h

	//tiene que leer los pines 6 y 7 del puerto G (portG_read) y devolver en la variable buttons
	//un 0 si no hay ning�n bot�n pulsado
	//1 si se a pulsado el bot�n 1
	//2 si se a pulsado el bot�n 2

	buttons = portG_read(6, &val);
	if(val == LOW)
		return 1;
	buttons = portG_read(7, &val);
	if(val == LOW)
		return 2;
	return 0;
}


