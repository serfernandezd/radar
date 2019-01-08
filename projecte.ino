// VALORS
#define LEDVERDE 2
#define LEDAMARILLO 3
#define LEDROJO 4
#define TRIGGER 5
#define ECHO 6
#define BUZZER 9
 
// Constants, with float for get the decimals
const float sonido = 34300.0; // Velocidad del sonido en cm/s
const float umbral1 = 30.0;
const float umbral2 = 20.0;
const float umbral3 = 10.0;
 
void setup() {
  // begininf of the fix area
  Serial.begin(9600);
 
  // output-input pins
  pinMode(LEDVERDE, OUTPUT);
  pinMode(LEDAMARILLO, OUTPUT);
  pinMode(LEDROJO, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(TRIGGER, OUTPUT);
  pinMode(BUZZER, OUTPUT);
 
  // turn off leds
  apagarLEDs();
 
}
 
void loop() {
  // turn on the trigger sensor
  iniciarTrigger();
 
  // quantify the ditance
  float distancia = calcularDistancia();
 
  // turn off leds
  apagarLEDs();
 
  // alert of zon 1
  if (distancia < umbral1)
  {
    // alert
    alertas(distancia);
  }
 
}
 
//  turn off leds
void apagarLEDs()
{
  //  turn off all leds
  digitalWrite(LEDVERDE, LOW);
  digitalWrite(LEDAMARILLO, LOW);
  digitalWrite(LEDROJO, LOW);
}
 
// there is any detection of ditance?
void alertas(float distancia)
{
  if (distancia < umbral1 && distancia >= umbral2)
  {
    //  turn on green led, sound 1
    digitalWrite(LEDVERDE, HIGH);
    tone(BUZZER, 2000, 200);
  }
  else if (distancia < umbral2 && distancia > umbral3)
  {
    //  turn on yellow led, sound 2
    digitalWrite(LEDAMARILLO, HIGH);
    tone(BUZZER, 2500, 200);
  }
  else if (distancia <= umbral3)
  {
    //  turn on red led, sound 3
    digitalWrite(LEDROJO, HIGH);
    tone(BUZZER, 3000, 200);
  }
}
 

// calculate the distance with decimals
float calcularDistancia()
{
  
  unsigned long tiempo = pulseIn(ECHO, HIGH);
 
  // distance * 0.000001 miliseconds
  float distancia = tiempo * 0.000001 * sonido / 2.0;
  Serial.print(distancia);
  Serial.print("cm");
  Serial.println();
  delay(500);
 
  return distancia;
}
 
// measure trigger ditance
void iniciarTrigger()
{
  //low trigger and wait 2 ms
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);
 
  // high trigger and wait 10 ms
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
 
  // begin with low trigger
  digitalWrite(TRIGGER, LOW);
}
