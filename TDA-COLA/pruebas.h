#ifndef __PRUEBAS_H__
#define __PRUEBAS_H__

// ------------------------------------------PRUEBAS SOBRE COLAS VACIAS/NULAS-------------------------------------------------
// pre:
// pod: imprime por pantalla si paso la prueba o si fallo
void siDesencoloUnaColaVaciaDeberiaDevolverError();

// pre:
// pod: imprime por pantalla si paso la prueba o si fallo
void siDesencoloUnaColaNulaDeberiaDevolverError();

// pre:
// pod: imprime por pantalla si paso la prueba o si fallo
void siEncoloEnUnaPilaNulaDeberiaDevolverError();

// pre:
// pod: imprime por pantalla si paso la prueba o si fallo
void siIntentoVerPrimeroDeColaVaciaDeberiaDevolverNULL();

//--------------------------------------------PRUEBAS SOBRE COLAS CON ELEMENTOS-------------------------------------------------

// pre:
// pod: imprime por pantalla si paso la prueba o si fallo
void siEncoloYDesencoloLaMismaCantidadDeElementosColaVaciaDeberiaDevolverTrue();

// pre:
// pod: imprime por pantalla si paso la prueba o si fallo
void siEncoloYDesencoloElementosDeberiaDevolverlosEnMismoOrden();

// pre:
// pod: imprime por pantalla si paso la prueba o si fallo
void siEncoloUnElementoNuloDeberiaEncolarCorrectamente();



#endif /* __PRUEBAS_H__ */