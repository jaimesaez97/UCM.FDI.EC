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
	int atras;	// 0 no, 1 sÌ
};

static struct RLstat RL = {
	.moving = 0,
	.speed = 5,
	.iter = 5,
	.direction = 0,
	.position = 0,
	.atras = 0
};

int setup(void)
{
	// configuramos B para que pines 9 y 10 sean de salida
	leds_init();

	// display de 8 segmentos -> no hace falta
	D8Led_init();
	D8Led_segment(RL.position);

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

	// rutina Delay invocada con valor 0 para su calibraciÛn
	Delay(0);



	return 0;
}

int loop(void)
{
	unsigned int buttons = read_button();

	if (buttons & BUT1) {	// led1 pulsado

	// COMPLETAR: utilizando la interfaz para los leds definida en leds.h
	// hay que conmutar el led1, si esta encendido apagarlo y viceversa
	// Tambi√©n hay que comutar la direcci√≥n del movimiento del led rotante
	// representado por el campo direction de la variable RL
		led1_switch();

//		if(RL.atras == 1){
//			RL.atras = 0;
//			RL.direction = (RL.direction + 1) % 2;
//		}
//		else{
//			RL.atras = 1;
//		}
		RL.atras = 1;



	}

	if (buttons & BUT2) {	// led2 pulsado
		// COMPLETAR: utilizando la interfaz para los leds definida en leds.h
		// hay que conmutar el led2
		// Tambi√©n hay que comutar el estado de movimiento del led rotante
		// representado por el campo moving de la variable RL, y en caso de
		// ponerlo en marcha debemos reiniciar el campo iter al valor del campo speed.
		led2_switch();

		RL.moving = 1;
	}

	if (RL.moving) {


		RL.iter--;
		if (RL.iter == 0) {
			// COMPLETAR: debemos hacer avanzar el led rotante una posici√≥n en
			// la direcci√≥n indicada por el campo direction de la variable RL.
			// La posici√≥n actual est√° representada en el campo position.
			// Recordar que queremos un movimiento circular, representado por
			// las 6 primeras posiciones en el array Segmentes del display de 8
			// segmentos, por lo que position debe estar siempre entre 0 y 5.

			if(!RL.atras){
				//deber· desplazar el segmento una posiciÛn y
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

		if(RL.atras){
		// CUENTA ATRAS
			D8Led_digit(3);
			Delay(10000);
			D8Led_digit(2);
			Delay(10000);
			D8Led_digit(1);
			Delay(10000);
			D8Led_digit(10000);
			RL.atras = 0;
			int i = 0;
			while(i < 10){
					Delay(1000);
					D8Led_digit(8);
					Delay(1000);
					D8Led_segment(6);
					i++;
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
