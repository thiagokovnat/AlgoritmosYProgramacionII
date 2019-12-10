#include "pruebas.h"



int main(){
	
	siInsertoYBorroEnListaNULLDeberiaDevolverError();

	siIntentoVerElUltimoEnListaVaciaDeberiaDevolverNULL();

	siIntentoVerElementoEnPosicionEnListaVaciaDeberiaDevolverNULL();

	siInsertoElementosListaElementosDeberiaDevolverLaCantidadDeElementosInsertados();

	siInsertoYBorroMismaCantidadDeElementosListaVaciaDeberiaDevolverTrue();

	siInsertoElementosEnDistintasPoisicionesVerElementoPosicionDeberiaDevolverLosElementos();

	siBorroElementosEnDistintasPosicionesVerElementoPosicionNoDeberiaDevolverEsosElementos();	

	siCreoUnIteradorConListaNulaDeberiaDevolverNULL();
	
	siRecorroTodaLaListaConElIteradorDeberiaDevolverTodosLosElementos();
	
	siCreoUnIteradorSobreListaNoVaciaTieneSiguienteDeberiaDevolverTrue();

	tieneSiguienteDeberiaDevolverFalseSiEstoyEnElUltimoElemento();

	imprimirElementosUsandoIteradorInterno();

    //insertar_cant();
}
