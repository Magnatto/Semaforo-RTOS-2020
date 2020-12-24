#include <Arduino.h>
#include "ChRt.h"

// Pino LED_BUILTIN no Arduino usualmente é o 13.

// Pinos de Entrada
#define PEDESTRE 2
#define SECUNDARIO 3
bool presencaPedestre = FALSE;
bool presencaSecundario = FALSE;

//Tamanho das threads
#define tamanhoThread1 64 //Tamanho em bytes da memória alocada a thread
#define tamanhoThread2 64
#define tamanhoThread3 64


#define Led1PrincipalVermelho  6; 
#define Led2PrincipalAmarelo 7;
#define Led3PrincipalVerde 8;     

int ativarcontador = 0;
int tempocontador =  0;
int terminoucontagem =  0;

int estado = 0;


//------------------------------------------------------------------------------
//                             Thread 1: Principal                            //
//------------------------------------------------------------------------------

static THD_WORKING_AREA(waThread1, tamanhoThread1); 

static THD_FUNCTION(Thread1, arg) 
{//Declara a função do Thread

  (void)arg;

   while(true)
    {
      
      if (!estado) {

        digitalWrite(13, HIGH);
      
      ativarcontador = 1;
      tempocontador = 5000;
      
        if (terminoucontagem=1){
          estado =2;
        }
      }
  
      if (estado) {
        digitalWrite(13, LOW);
        tempocontador = 5000;
        if (terminoucontagem=1){
          estado =1;
        }
      }
  }

}

//------------------------------------------------------------------------------
//                              Thread 2: Contador                            //
//------------------------------------------------------------------------------
//Realiza os tempos de espera de cada estado

static THD_WORKING_AREA(waThread2, tamanhoThread2); 

static THD_FUNCTION(Thread2, arg) 
{//Declara a função do Thread

  (void)arg;

   while(true)
    {
      if (ativarcontador)
      {
        chThdSleepMilliseconds(tempocontador);  //Timer de tempocontador milisegundos
        tempocontador = 0;
        ativarcontador = 0;
        terminoucontagem = 1;
      }
      chThdSleepMilliseconds(1000);             //Período aproximado da thread
    
  }

}


//------------------------------------------------------------------------------
// Thread 3, leitura da entrada
//
//Lê as entradas dos sensores de pedestre e semáforo secundário e atualiza a cada segundo
static THD_WORKING_AREA(waThread3, tamanhoThread3); 
  
static THD_FUNCTION(Thread3, arg)
{//Declara a função do Thread
  chThdSleepMilliseconds(20);
  (void)arg;

  while(true)
    {//Loop infinito
      presencaPedestre = digitalRead(PEDESTRE);
      presencaSecundario = digitalRead(SECUNDARIO);
      chThdSleepMilliseconds(500);
      if(!presencaPedestre) Serial.println("Tem gente! ");
      if(!presencaSecundario) Serial.println("Tem carro! ");
      digitalWrite(LED_BUILTIN, HIGH);
      chThdSleepMilliseconds(500);
      digitalWrite(LED_BUILTIN, LOW);
    }
}

// continua setup() ao chamar chBegin().
void chSetup() {
  // Inicializa as threads.
  chThdCreateStatic(waThread1, sizeof(waThread1),
    NORMALPRIO + 2, Thread1, NULL);
  
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

  pinMode(13, OUTPUT);

  // Inicialisa o OS e chama chSetup.
  chBegin(chSetup);
  // chBegin() reseta as pilhas e nunca deve retornar.
  while (true) {}
}
//------------------------------------------------------------------------------
// loop() é a thread principal.  Não utilizada.
void loop() {
}