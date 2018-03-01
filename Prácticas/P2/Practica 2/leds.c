/*-------------------------------------------------------------------
**
**  Fichero:

**    leds.c
**
**    Estructura de Computadores
**    Dpto. de Arquitectura de Computadores y Autom�tica
**    Facultad de Inform�tica. Universidad Complutense de Madrid
**
**  Prop�sito:
**    Contiene las implementaciones de las funciones
**    para el acceso a los leds de la placa de prototipado
**
**  Notas de dise�o:
**    Equivale al fichero hom�nimo usado en Fundamentos de Computadores
**
**-----------------------------------------------------------------*/

#include "44b.h"
#include "leds.h"
#include "gpio.h"

// M�scaras de bits
#define LED1 0x01
#define LED2 0x02
#define BIT_LED1 9
#define BIT_LED2 10

// status representa el estado de los leds
// solo tienen sentido los dos bites menos
// significativos, cada uno para un led
// 1 encendido y 0 apagado
static unsigned int status = 0;

void leds_init( void )
{
	//COMPLETAR usando el interfaz del puerto B definido en gpio.h
	//hay que configurar los pines 9 y 10 como pines de salida
	enum port_mode mode;
	mode = OUTPUT;

	portB_conf(9, OUTPUT);
	portB_conf(10, OUTPUT);

	leds_display( status );
}

void led1_on( void )
{
	status |=  LED1;
	leds_display( status );
}

void led1_off( void )
{
	status &=  ~LED1;
	leds_display( status );
}

void led2_on( void )
{
	status |=  LED2;
	leds_display( status );
}

void led2_off( void )
{
	status &=  ~LED2;
	leds_display( status );
}

void led1_switch( void )
{
	status ^= LED1;
	leds_display( status );
}

void led2_switch( void )
{
	status ^= LED2;
	leds_display( status );
}

void leds_switch( void ){
	status ^= (LED1 | LED2);
	leds_display( status );
}

void leds_display( unsigned int leds_status )
{
	status = leds_status;
	
	enum digital level;

	// LED 1
	if( status & LED1 ){
		//COMPLETAR usando el interfaz del puerto B definido en gpio.h
		//hay que poner a nivel bajo el bit correspondiente al led 1
		level = LOW;
		portB_write(9, level);

	}
	else{

		//COMPLETAR usando el interfaz del puerto B definido en gpio.h
		//hay que poner a nivel alto el bit correspondiente al led 1
		level = HIGH;
		portB_write(9, level);

	}
	// LED 2
	if( status & LED2 ){
		//COMPLETAR usando el interfaz del puerto B definido en gpio.h
		//hay que poner a nivel bajo el bit correspondiente al led 2
		level = LOW;
		portB_write(10, level);

	}
	else{
		//COMPLETAR usando el interfaz del puerto B definido en gpio.h
		//hay que poner a nivel alto el bit correspondiente al led 2
		level = HIGH;
		portB_write(10, level);
	}

}
