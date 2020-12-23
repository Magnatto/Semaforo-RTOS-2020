#include <Arduino.h>
#include "ChRt.h"
// Pino LED_BUILTIN no Arduino usualmente é o 13.

// Pinos de Entrada
#define PEDESTRE 2
#define SECUNDARIO 3
bool presencaPedestre = FALSE;
bool presencaSecundario = FALSE;

// Pinos de Saída
#define vermelhoPedestre 13
bool pedestrePisca=FALSE;
#define verdePedestre 5

#define vermelhoSecundario 6
#define amareloSecundario 7
#define verdeSecundario 8

#define vermelhoPrincipal 9
#define amareloPrincipal 10
#define verdePrincipal 11

//Tamanho das threads
#define tamanhoThread1 64 //Tamanho em bytes da memória alocada a thread
#define tamanhoThread2 64
#define tamanhoThread3 64

//------------------------------------------------------------------------------
// Thread 2, piscada do sinal de pedestre
//
//Pisca o sinal de pedestre com uma frequência de 2Hz
static THD_WORKING_AREA(waThread2, tamanhoThread2); 


static THD_FUNCTION(Thread2, arg)
{//Declara a função do Thread

  (void)arg;

  while(true)
    {//Loop infinito
      if(pedestrePisca)
      {
       for (uint8_t i = 0; i < 8; i++)
       {
        chThdSleepMilliseconds(250);
        digitalWrite(vermelhoPedestre, HIGH);
        chThdSleepMilliseconds(250);
        digitalWrite(vermelhoPedestre, LOW);
       }
        pedestrePisca=FALSE;
        Serial.println("Ja foi");
      }
      chThdSleepMilliseconds(20); // Período da thread pra permitir outras threads
    }
}

//------------------------------------------------------------------------------
// Thread 3, leitura da entrada
//
//Lê as entradas dos sensores de pedestre e semáforo secundário e atualiza a cada segundo
static THD_WORKING_AREA(waThread3, tamanhoThread3); 


static THD_FUNCTION(Thread3, arg)
{//Declara a função do Thread

  (void)arg;

  while(true)
    {//Loop infinito
      presencaPedestre = digitalRead(PEDESTRE);
      presencaSecundario = digitalRead(SECUNDARIO);
      if(!presencaPedestre) Serial.println("Tem gente! ");
      if(!presencaSecundario){
         pedestrePisca=HIGH;
         Serial.println("Pedestre!");
      }
      chThdSleepMilliseconds(1000);
    }
}

// continua setup() ao chamar chBegin().
void chSetup() {
  // Inicializa as threads.
  /*chThdCreateStatic(waThread1, sizeof(waThread1),
    NORMALPRIO + 2, Thread1, NULL);
*/
  chThdCreateStatic(waThread2, sizeof(waThread2),
    NORMALPRIO + 1, Thread2, NULL);

  chThdCreateStatic(waThread3, sizeof(waThread3),
    NORMALPRIO, Thread3, NULL);
}
//------------------------------------------------------------------------------
void setup() {
  
  Serial.begin(9600);
  
  // Inicializando entradas:
  pinMode(PEDESTRE, INPUT_PULLUP);
  pinMode(SECUNDARIO, INPUT_PULLUP);
  pinMode(verdePedestre, OUTPUT);

  // Inicialisa o OS e chama chSetup.
  chBegin(chSetup);
  // chBegin() reseta as pilhas e nunca deve retornar.
  while (true) {}
}
//------------------------------------------------------------------------------
// loop() é a thread principal.  Não utilizada.
void loop() {
}