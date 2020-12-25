#include <Arduino.h>
#include "ChRt.h"

// Pino LED_BUILTIN no Arduino usualmente é o 13.

// Pinos de Entrada
#define PEDESTRE 2
#define SECUNDARIO 3

//Tamanho das threads
#define tamanhoThread1 64 //Tamanho em bytes da memória alocada a thread
#define tamanhoThread2 64
#define tamanhoThread3 64

#define LEDPRINCIPALVERMELHO 12
#define LEDPRINCIPALAMARELO 11
#define LEDPRINCIPALVERDE 10

#define LEDSECUNDARIAVERMELHO 7
#define LEDSECUNDARIAAMARELO 6
#define LEDSECUNDARIAVERDE 5

#define LEDPEDESTREVERMELHO 9
#define LEDPEDESTREVERDE 8



bool sensorPedestre = FALSE;
bool sensorSecundaria = FALSE;
int ativarcontador = 0;
int tempocontador =  100;
int terminoucontagem =  0;
int estado = 0;
int flagpedestre = 0;
int flagblink = 0;


//------------------------------------------------------------------------------
//                             Thread 1: Principal                            //
//------------------------------------------------------------------------------

static THD_WORKING_AREA(waThread1, tamanhoThread1); 

static THD_FUNCTION(Thread1, arg) 
{//Declara a função do Thread

  (void)arg;

  while(true)
  {
       
      switch (estado)
      {
        case 0:
          Serial.println("estado 0 - transicao");
          flagpedestre=0;
        break;

        case 1:
          Serial.println("estado 1 - transicao");
          if(sensorPedestre)
            estado=2;
          else if (!sensorPedestre && sensorSecundaria)
            estado=3;
        break;
     
        case 2:
          Serial.println("estado 2 - transicao");
        break;

        case 3:
          Serial.println("estado 3 - transicao");
        break;

        case 4:
          Serial.println("estado 4 - transicao");
          flagpedestre=1;
        break;

        case 5:
          Serial.println("estado 5 - transicao");
        break;

        case 6:
          Serial.println("estado 6 - transicao");
          if (flagblink>=4){
            flagblink=0;
            if(sensorSecundaria) estado=7;
            else estado=0;
          }
        break;

        case 7:
          Serial.println("estado 7 - transicao");
        break;

        case 8:
          Serial.println("estado 8 - transicao");
        break;
     
      }
      
        chThdSleepMilliseconds(200);
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
        switch (estado)
        {
          case 0:
            Serial.println("estado 0 - ativacao");
            digitalWrite(LEDPRINCIPALVERMELHO, LOW);
            digitalWrite(LEDPRINCIPALAMARELO, LOW);
            digitalWrite(LEDPRINCIPALVERDE, HIGH);

            digitalWrite(LEDSECUNDARIAVERMELHO, HIGH);
            digitalWrite(LEDSECUNDARIAAMARELO, LOW);
            digitalWrite(LEDSECUNDARIAVERDE, LOW);
            
            digitalWrite(LEDPEDESTREVERMELHO, HIGH);
            digitalWrite(LEDPEDESTREVERDE, LOW);
            tempocontador=10000;
            chThdSleepMilliseconds(tempocontador);  //Timer de tempocontador milisegundos
            estado=1;
          break;

          case 1:
            Serial.println("estado 1 - ativacao");
            digitalWrite(LEDPRINCIPALVERMELHO, LOW);
            digitalWrite(LEDPRINCIPALAMARELO, LOW);
            digitalWrite(LEDPRINCIPALVERDE, HIGH);

            digitalWrite(LEDSECUNDARIAVERMELHO, HIGH);
            digitalWrite(LEDSECUNDARIAAMARELO, LOW);
            digitalWrite(LEDSECUNDARIAVERDE, LOW);
            
            digitalWrite(LEDPEDESTREVERMELHO, HIGH);
            digitalWrite(LEDPEDESTREVERDE, LOW);
          break;
      
          case 2:
            Serial.println("estado 2 - ativacao");
            digitalWrite(LEDPRINCIPALVERMELHO, LOW);
            digitalWrite(LEDPRINCIPALAMARELO, HIGH);
            digitalWrite(LEDPRINCIPALVERDE, LOW);

            digitalWrite(LEDSECUNDARIAVERMELHO, HIGH);
            digitalWrite(LEDSECUNDARIAAMARELO, LOW);
            digitalWrite(LEDSECUNDARIAVERDE, LOW);
            
            digitalWrite(LEDPEDESTREVERMELHO, HIGH);
            digitalWrite(LEDPEDESTREVERDE, LOW);

            tempocontador=2000;
            chThdSleepMilliseconds(tempocontador);  //Timer de tempocontador milisegundos
            estado=4;
          break;
      
          case 3:
            Serial.println("estado 3 - ativacao");
            digitalWrite(LEDPRINCIPALVERMELHO, LOW);
            digitalWrite(LEDPRINCIPALAMARELO, HIGH);
            digitalWrite(LEDPRINCIPALVERDE, LOW);

            digitalWrite(LEDSECUNDARIAVERMELHO, HIGH);
            digitalWrite(LEDSECUNDARIAAMARELO, LOW);
            digitalWrite(LEDSECUNDARIAVERDE, LOW);
            
            digitalWrite(LEDPEDESTREVERMELHO, HIGH);
            digitalWrite(LEDPEDESTREVERDE, LOW);

            tempocontador=2000;
            chThdSleepMilliseconds(tempocontador);  //Timer de tempocontador milisegundos
            estado=7;
          break;
      
          case 4:
            Serial.println("estado 4 - ativacao");
            digitalWrite(LEDPRINCIPALVERMELHO, HIGH);
            digitalWrite(LEDPRINCIPALAMARELO, LOW);
            digitalWrite(LEDPRINCIPALVERDE, LOW);

            digitalWrite(LEDSECUNDARIAVERMELHO, HIGH);
            digitalWrite(LEDSECUNDARIAAMARELO, LOW);
            digitalWrite(LEDSECUNDARIAVERDE, LOW);
            
            digitalWrite(LEDPEDESTREVERMELHO, LOW);
            digitalWrite(LEDPEDESTREVERDE, HIGH);

            tempocontador=3000;
            chThdSleepMilliseconds(tempocontador);  //Timer de tempocontador milisegundos
            estado=5;
          break;
      
          case 5:
            Serial.println("estado 5 - ativacao");
            digitalWrite(LEDPRINCIPALVERMELHO, HIGH);
            digitalWrite(LEDPRINCIPALAMARELO, LOW);
            digitalWrite(LEDPRINCIPALVERDE, LOW);

            digitalWrite(LEDSECUNDARIAVERMELHO, HIGH);
            digitalWrite(LEDSECUNDARIAAMARELO, LOW);
            digitalWrite(LEDSECUNDARIAVERDE, LOW);
            
            digitalWrite(LEDPEDESTREVERMELHO, HIGH);
            digitalWrite(LEDPEDESTREVERDE, LOW);

            tempocontador=500;
            chThdSleepMilliseconds(tempocontador);  //Timer de tempocontador milisegundos
            flagblink++;
            estado=6;
          break;
      
          case 6:
            Serial.println("estado 6 - ativacao");
            digitalWrite(LEDPRINCIPALVERMELHO, HIGH);
            digitalWrite(LEDPRINCIPALAMARELO, LOW);
            digitalWrite(LEDPRINCIPALVERDE, LOW);

            digitalWrite(LEDSECUNDARIAVERMELHO, HIGH);
            digitalWrite(LEDSECUNDARIAAMARELO, LOW);
            digitalWrite(LEDSECUNDARIAVERDE, LOW);
            
            digitalWrite(LEDPEDESTREVERMELHO, LOW);
            digitalWrite(LEDPEDESTREVERDE, LOW);

            tempocontador=500;
            chThdSleepMilliseconds(tempocontador);  //Timer de tempocontador milisegundos
            flagblink++;
            estado=5;
          break;
      
          case 7:
            Serial.println("estado 7 - ativacao");
            digitalWrite(LEDPRINCIPALVERMELHO, HIGH);
            digitalWrite(LEDPRINCIPALAMARELO, LOW);
            digitalWrite(LEDPRINCIPALVERDE, LOW);

            digitalWrite(LEDSECUNDARIAVERMELHO, LOW);
            digitalWrite(LEDSECUNDARIAAMARELO, LOW);
            digitalWrite(LEDSECUNDARIAVERDE, HIGH);
            
            digitalWrite(LEDPEDESTREVERMELHO, HIGH);
            digitalWrite(LEDPEDESTREVERDE, LOW);

            tempocontador=6000;
            chThdSleepMilliseconds(tempocontador);  //Timer de tempocontador milisegundos
            estado=8;
          break;
      
          case 8:
            Serial.println("estado 8 - ativacao");
            digitalWrite(LEDPRINCIPALVERMELHO, HIGH);
            digitalWrite(LEDPRINCIPALAMARELO, LOW);
            digitalWrite(LEDPRINCIPALVERDE, LOW);

            digitalWrite(LEDSECUNDARIAVERMELHO, LOW);
            digitalWrite(LEDSECUNDARIAAMARELO, HIGH);
            digitalWrite(LEDSECUNDARIAVERDE, LOW);
            
            digitalWrite(LEDPEDESTREVERMELHO, HIGH);
            digitalWrite(LEDPEDESTREVERDE, LOW);

            tempocontador=2000;
            chThdSleepMilliseconds(tempocontador);  //Timer de tempocontador milisegundos
            if (sensorPedestre && flagpedestre==0){
              estado=4;
            }else{
              estado=0;
            }
          break;
        }
      

        chThdSleepMilliseconds(200);
  }

}


//------------------------------------------------------------------------------
// Thread 3, leitura da entrada
//      digitalWrite(10, !digitalRead (10));
//Lê as entradas dos sensores de pedestre e semáforo secundário e atualiza a cada segundo
static THD_WORKING_AREA(waThread3, tamanhoThread3); 
  
static THD_FUNCTION(Thread3, arg)
{//Declara a função do Thread
  chThdSleepMilliseconds(20);
  (void)arg;

  while(true)
    {//Loop infinito
      sensorPedestre = digitalRead(PEDESTRE);
      sensorSecundaria = digitalRead(SECUNDARIO);
      chThdSleepMilliseconds(500);
      if(sensorPedestre) Serial.println("Tem pedestre! ");
      if(sensorSecundaria) Serial.println("Tem carro na secundaria! ");
      digitalWrite(LED_BUILTIN, HIGH);
      chThdSleepMilliseconds(500);
      digitalWrite(LED_BUILTIN, LOW);

        chThdSleepMilliseconds(20);
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
  pinMode(PEDESTRE, INPUT);
  pinMode(SECUNDARIO, INPUT);
;

  pinMode(LEDPRINCIPALVERMELHO, OUTPUT);
  pinMode(LEDPRINCIPALAMARELO, OUTPUT);
  pinMode(LEDPRINCIPALVERDE, OUTPUT);

  pinMode(LEDSECUNDARIAVERMELHO, OUTPUT);
  pinMode(LEDSECUNDARIAAMARELO, OUTPUT);
  pinMode(LEDSECUNDARIAVERDE, OUTPUT);

  pinMode(LEDPEDESTREVERMELHO, OUTPUT);
  pinMode(LEDPEDESTREVERDE, OUTPUT);


  // Inicialisa o OS e chama chSetup.
  chBegin(chSetup);
  // chBegin() reseta as pilhas e nunca deve retornar.
  while (true) {}
}
//------------------------------------------------------------------------------
// loop() é a thread principal.  Não utilizada.
void loop() {
}