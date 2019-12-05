#include "pila.h"
#include <stdbool.h>
#include <stdio.h>
#include "pruebas.h"


int main(){

	siApiloYDesapiloMismoVolumenPilaVaciaDeberiaDevolverTrue();

	siIntentoDesapilarUnaPilaVaciaDeberiaDevolverError();

	siIntentoVerElTopeDePilaVaciaDeberiaDevolverNULL();

	siLlenoLaCantidadInicialElTamanioDeberiaDuplicarse();

	siDesapiloLaMitadDeElementosLaPilaDeberiaAchicarse();

	siApiloSobrePilaNulaDeberiaDevolverError();
	
	siApiloElementosYLosDesapiloDeberiaDevolverlosEnOrdenInverso();

	return 0;
}