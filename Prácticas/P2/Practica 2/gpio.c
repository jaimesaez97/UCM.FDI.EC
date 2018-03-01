/*		DUDAS:

 * 		1.- En portG_read() se lee el bit pin*2. En buttons.c, nos piden que
 * 		leamos el bit 6 y 7 del puerto G. ¿Cómo se hace si, según está,
 * 		solo se pueden leer bits pares? ¿O cambiamos la funcion portG_read()?
 *		2.- Preguntar por button.c/read_button()
 *		3.- En portG_eint_trig() hay que usar PIN o lo ponemos a capon?
 *		4.- this/portG_read() -> PIN O POS EN IF
 *
 *		COMPROBAR:
 *		1.-this/portG_read() -> val = high -> pulsado = no?
 *		3.-this/portG_conf_pup() -> ENABLE así o al revés?
 *
 */
#include "44b.h"
#include "gpio.h"

// puerto B
#define rPCONB (*(volatile unsigned *)0x1d20008)
#define rPDATB (*(volatile unsigned *)0x1d2000c)
// puerto G
#define rEXTINT (*(volatile unsigned *)0x1d20050)
#define rPDATG (*(volatile unsigned *)0x1d20044)


/* Port B interface implementation */

/*	Puerto B: 11 bits
 * 	 	-R.Datos 	: PDATB
 * 	 	-R.Control  : PCONB
 *
 * */

int portB_conf(int pin, enum port_mode mode)
{
	int ret = 0;
	if (pin < 0 || pin > 10)
		return -1;

	if (mode == SIGOUT){
		//COMPLETAR: Configurar el pin del puerto B
		//para que salga la senal correspondiente del controlador de memoria
		rPCONB |= (0x1 << pin); 	// pongo bit PIN a 1
	}
	else if (mode == OUTPUT){
		///COMPLETAR: Configurar el pin del puerto B
		//para que sea de salida
		rPCONB &= ~(0x1 << pin); //pongo bit PIN a 0
	}
	else
		ret = -1;

	return ret;
}

int portB_write(int pin, enum digital val)
{
	if (pin < 0 || pin > 10)
		return -1;

	if (val < 0 || val > 1)
		return -1;

	if (val){
		//COMPLETAR: poner en el pin del puerto B
		//el valor adecuado para que el led se apague(1)
		rPDATB |= (0x1 << pin);	// pongo bit PIN a 1

	}
	else{

		//COMPLETAR: poner en el pin del puerto B
		//el valor adecuado para que el led se encienda(0)
		rPDATB &= ~(0x1 << pin);	// pongo bit PIN a 0

	}
	return 0;
}

/* Port G interface implementation */

/*
 * 	Puerto G (bits 15-0):
 * 		-PDATG: 1 pulsado, 0 no.
 * 		-PUPG:  Permite activar 1 resistencia por cada pin
 * 		-PCONG: Permite configurar pines:
 * 			+ 00 -> pin = entrada
 * 			+ 11 -> activar interrupcion
 * 			+ ¿salida?
 * */


int portG_conf(int pin, enum port_mode mode)
{
	//La variable pos indica el primer bit del registro de control del puerto G que corresponde al pin
	int pos = pin*2;

	if (pin < 0 || pin > 7)
		return -1;

	switch (mode) {
		case INPUT:	//00
			//COMPLETAR: Configurar el pin del puerto G
			//para que sea de entrada
			rPCONG &= ~(0x3 << pos);	// pongo 00
			break;
		case OUTPUT: //01
			//COMPLETAR: Configurar el pin del puerto G
			//para que sea de salida
			rPCONG &= ~(0x3 << pos);	// pongo 00
			rPCONG |= (0x1 << pos);		// pongo 01

			break;
		case SIGOUT: //10
			//COMPLETAR: Configurar el pin del puerto G
			//para que salga la señal interna correspondiente
			rPCONG &= ~(0x3 << pos);	// pongo 00
			rPCONG |= (0x2 << pos);		// pongo 10


			break;
		case EINT: //11
			//COMPLETAR: Configurar el pin del puerto G
			//para habilitar la generación de interrupciones externas

			rPCONG |= (0x3 << pos);	// pongo 11

			break;
		default:
			return -1;
	}

	return 0;
}

int portG_eint_trig(int pin, enum trigger trig)
{
	//La variable pos indica el primer bit del registro EXTINT del puerto G que corresponde al pin
	int pos = pin*4;

	if (pin < 0 || pin > 7)
		return -1;

	// pongo todo a 0
	rEXTINT &= ~(0x7 << pos);

	switch (trig) {
		case LLOW:	//000
			// COMPLETAR: configurar el pin del puerto G para que genere interrupciones externas por nivel bajo
			rEXTINT &= ~(0x7 << pos); // no necesario
			break;
		case LHIGH:	//001
			// COMPLETAR: configurar el pin del puerto G para que genere interrupciones externas por nivel alto
			rEXTINT |= ~(0x6 << pos);
			break;
		case FALLING:	//01x -> 011(3) o 010(2)
			// COMPLETAR: configurar el pin del puerto G para que el pin genere interrupciones externas por flanco de bajada
			rEXTINT |= (0x2 << pos);
			break;
		case RISING:	//10x -> 100(4) o 101(5)
			// COMPLETAR: configurar el pin del puerto G para que el pin genere interrupciones externas por flanco de subida
			rEXTINT |= (0x4 << pos);
			break;
		case EDGE:		//11x -> 110(6) o 111(7)
			// COMPLETAR: configurar el pin del puerto G para que el pin genere interrupciones externas por cualquier flanco
			rEXTINT |= (0x7 << pos);
			break;
		default:
			return -1;
	}
	return 0;
}


int portG_read(int pin, enum digital* val)
{
	int pos = pin*2;

	if (pin < 0 || pin > 7)
		return -1;

	if (rPCONG & (0x3 << pos))
		return -1;
	//COMPLETAR la condicion del if: comprobar si el pin del registro de datos del puerto G es un 1)

	if((rPDATG & (0x1 << pin)))	// ¿PIN O POS?
		*val=HIGH;	// HIGH = NOPULSADO?
	else
		*val=LOW;	// LOW = PULSADO?

	return 0;
}

int portG_conf_pup(int pin, enum enable st)
{
	if (pin < 0 || pin > 7)
		return -1;

	if (st != ENABLE && st != DISABLE)
		return -1;

	if (st == ENABLE){
		//COMPLETAR: activar la resistencia de pull-up del pin del puerto G
		rPUPG &= ~(0x1 << pin);	// pongo PIN a 0
	}
	else{
		//COMPLETAR: desactivar la resistencia de pull-up del pin del puerto G
		rPUPG |= (0x1 << pin);	// pongo PIN a 1
	}
	return 0;
}


int portG_write(int pin, enum digital val)
{
	int pos = pin*2;

	if (pin < 0 || pin > 7)
		return -1;

	if (val < 0 || val > 1)
		return -1;

	if ((rPCONG & (0x3 << pos)) != (0x1 << pos))
		return -1;

	if (val)
		rPDATG|= ~(0x1<<pin);
	else
		rPDATG &= ~(0x1<<pin);

	return 0;
}
