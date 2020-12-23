#include <Arduino.h>

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


const int Led1PrincipalVermelho =  6; 
const int Led2PrincipalAmarelo =  7;
const int Led3PrincipalVerde =  8;     

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
  /*chThdCreateStatic(waThread1, sizeof(waThread1),
    NORMALPRIO + 2, Thread1, NULL);

  chThdCreateStatic(waThread2, sizeof(waThread2),
    NORMALPRIO + 1, Thread2, NULL);
*/
  chThdCreateStatic(waThread3, sizeof(waThread3),
    NORMALPRIO, Thread3, NULL);
}
//------------------------------------------------------------------------------
void setup() {
  
  Serial.begin(9600);
  
  // Inicializando entradas:
  pinMode(PEDESTRE, INPUT_PULLUP);
  pinMode(SECUNDARIO, INPUT_PULLUP);

  // Inicialisa o OS e chama chSetup.
  chBegin(chSetup);
  // chBegin() reseta as pilhas e nunca deve retornar.
  while (true) {}
}
//------------------------------------------------------------------------------
// loop() é a thread principal.  Não utilizada.
void loop() {
}