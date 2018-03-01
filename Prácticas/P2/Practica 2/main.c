// ULTIMO
#include <stdio.h>
#include "44b.h"
#include "button.h"
#include "leds.h"
#include "utils.h"
#include "D8Led.h"
#include "gpio.h"

struct RLstat {
	int moving;
	int speed;
	int iter;
	int direction;
	int position;
};

static struct RLstat RL = {
	.moving = 0,
	.speed = 5,
	.iter = 0,
	.direction = 0,
	.position = 0,
};

int setup(void)
{
	// configuramos B para que pines 9 y 10 sean de salida
	leds_init();

	// configuramos G para que pines 6 y 7 sean de entrada
	enum port_mode mode;
	mode = INPUT;
	portG_conf(6, mode);
	portG_conf(7, mode);

	// activamos resistencias de pull-up
	enum enable st;
	st = ENABLE;
	portG_conf_pup(6, st);
	portG_conf_pup(7, st);

	// rutina Delay invocada con valor 0 para su calibraci�n
	Delay(0);

	// display de 8 segmentos -> no hace falta
	D8Led_init();
	D8Led_segment(RL.position);

	return 0;
}

int loop(void)
{
	unsigned int buttons = read_button();

	if (buttons & BUT1) {	// led1 pulsado

	// COMPLETAR: utilizando la interfaz para los leds definida en leds.h
	// hay que conmutar el led1, si esta encendido apagarlo y viceversa
	// También hay que comutar la dirección del movimiento del led rotante
	// representado por el campo direction de la variable RL
		led1_switch();

		RL.direction = (RL.direction + 1) % 2;

	}

	if (buttons & BUT2) {	// led2 pulsado
		// COMPLETAR: utilizando la interfaz para los leds definida en leds.h
		// hay que conmutar el led2
		// También hay que comutar el estado de movimiento del led rotante
		// representado por el campo moving de la variable RL, y en caso de
		// ponerlo en marcha debemos reiniciar el campo iter al valor del campo speed.
		led2_switch();

		RL.moving = (RL.moving + 1) % 2;
	}

	if (RL.moving) {

		RL.iter--;
		if (RL.iter == 0) {
			// COMPLETAR: debemos hacer avanzar el led rotante una posición en
			// la dirección indicada por el campo direction de la variable RL.
			// La posición actual está representada en el campo position.
			// Recordar que queremos un movimiento circular, representado por
			// las 6 primeras posiciones en el array Segmentes del display de 8
			// segmentos, por lo que position debe estar siempre entre 0 y 5.


			//deber� desplazar el segmento una posici�n y
			//reiniciar dicho contador.
			RL.iter = RL.speed;
			if(RL.direction == 0){ // ANTIHORARIO ( En Segments de la posicion 5 a 0)
				RL.position--;
				if(RL.position < 0)
					RL.position = 5;
			}
			else{ // SENTIDO HORARIO (de 0 a 5)
				RL.position++;
				if(RL.position > 5)
					RL.position = 0;
			}

		}
	}
	
	
    D8Led_segment(RL.position);

	Delay(2000); // espera de 200ms para que el bucle se repita 5 veces por segundo
	return 0;
}


int main(void)
{
	setup();

	while (1) {
		loop();
	}
}
