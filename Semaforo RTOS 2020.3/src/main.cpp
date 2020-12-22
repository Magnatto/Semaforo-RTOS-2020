#include <Arduino.h>  //Biblioteca para funções do Arduino
#include "ChRt.h"   //Biblioteca para uso do ChibiOS

// Pino LED_BUILTIN no Arduino usualmente é o 13.
#define tamanhoThread1 64 //Tamanho em bytes da memória alocada a thread
#define tamanhoThread2 64

uint8_t state = 0;


//------------------------------------------------------------------------------
// Thread 1, acende o LED
//
//Declara área de trabalho e tamanho da memória alocada a essa área
static THD_WORKING_AREA(waThread1, tamanhoThread1); 

static THD_FUNCTION(Thread1, arg)
{//Declara a função do Thread

  (void)arg;
  pinMode(LED_BUILTIN, OUTPUT);
  while(true)
    {//Loop infinito
      if (state)
      {
        digitalWrite(LED_BUILTIN, HIGH);
        chThdSleepMilliseconds(500);  //Período aproximado de piscada
        state=0;
        Serial.print("cyka ");
      }
      chThdSleepMilliseconds(1000); //Período aproximado da thread
    }
}
//------------------------------------------------------------------------------
// Thread 2, apaga o LED
//
//Declara área de trabalho e tamanho da memória alocada a essa área
static THD_WORKING_AREA(waThread2, tamanhoThread2);


static THD_FUNCTION(Thread2, arg)
{//Declara a função do Thread
  pinMode(LED_BUILTIN, OUTPUT);
  (void)arg;
  while(true)
  {
    if (!state)
    {
      digitalWrite(LED_BUILTIN, LOW);
      chThdSleepMilliseconds(500);  //Período aproximado de piscada
      state=1;
      Serial.print("blyat ");
    }
    chThdSleepMilliseconds(1000); //Período aproximado da thread
  }
}
//------------------------------------------------------------------------------

// continua setup() ao chamar chBegin().
void chSetup() {
  // Inicializa as threads.
  chThdCreateStatic(waThread1, sizeof(waThread1),
    NORMALPRIO + 2, Thread1, NULL);

  chThdCreateStatic(waThread2, sizeof(waThread2),
    NORMALPRIO + 1, Thread2, NULL);
}
//------------------------------------------------------------------------------
void setup() {
  // Inicialisa o OS e chama chSetup.
  Serial.begin(9600);
  chBegin(chSetup);
  // chBegin() reseta as pilhas e nunca deve retornar.
  while (true) {}
}
//------------------------------------------------------------------------------
// loop() é a thread principal.  Não utilizada.
void loop() {
}