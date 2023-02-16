/*
comentada e função "desligar bomba" uma vez que com o erro tendendo a zero o valor 
do pwm também tende a zero, ou seja, potência muito baixa ou nula
os valores de kp, ki e kd foram os sugeridos pelo Marcos
*/

#include <Arduino.h>

# define pinSensorTrig 8
# define pinSensorEcho 7
# define pinBomba 11
# define altura 23.6
# define vsom 0.0343
# define nivel_max 15.00
# define kp 80.00
# define ki 0.1
# define kd 35.00

bool atraso = true;
bool cabecalho;
float time_now;
float time_after;
double distancia;
double nivel;
double valor_ref;
double erro_previo;
double erro_atual;
double erro_acumulado;

//função que aciona a bomba com a potência de acordo com o valor de pwm (0 a 255)
void ligarBomba(int valor_pwm)
{
  analogWrite(pinBomba, valor_pwm);
}

//função que define o valor do pwm
int definirPwm(double valor_nivel, double erro_somatorio, double erro_anterior)
{  
  double erro_atual = valor_ref - valor_nivel;

  //é uma aproximação da integral (arquivo "Integral.png")
  erro_somatorio = (erro_atual * (time_now - time_after) + erro_somatorio);

  //é uma aproximação da derivada
  double derivada_aprox = (erro_atual - erro_anterior)/(time_now - time_after);

  int pwm = erro_atual * kp + (ki * erro_somatorio) + kd * derivada_aprox;

  //o valor do pwm não pode ser menor que 0 nem maior que 255
  if (pwm > 255) pwm = 255;
  else if (pwm < 0) pwm = 0;

  /*na próxima iteração o valor atual de tempo será o valor anterior de tempo
  o mesmo raciocínio serve para o erro*/
  time_after = time_now;
  erro_anterior = erro_atual;

  return pwm;
}

void setup()
{
  pinMode(pinSensorTrig, OUTPUT);
  pinMode(pinSensorEcho, INPUT);
  pinMode(pinBomba, OUTPUT);
  cabecalho = 1;
  valor_ref = nivel_max;
  Serial.begin(9600);
  time_after = 0;
  erro_previo = 0;
}

void loop()
{  
  time_now = millis() / 1000;

  digitalWrite(pinSensorTrig, HIGH);
  delayMicroseconds(15);
  digitalWrite(pinSensorTrig, LOW);

  distancia = (vsom * pulseIn(pinSensorEcho, HIGH))/2;  
  nivel = altura - distancia;  

  /*O valor do pwm é passado para a função "ligarBomba".
  Esse valor é calculado na função "definirPwm, que apenas retorna o valor do pwm*/
  double valor_pwm = definirPwm(nivel, erro_acumulado, erro_previo);

  ligarBomba(valor_pwm);

  //serve para imprimir o cabeçalho na primeira vez
  if (cabecalho == 1){
    Serial.print("tempo;nivel\n");
    cabecalho = 0;
  }
  
  Serial.print(time_now);
  Serial.print(";");
  Serial.println(nivel);
  Serial.print(";");
  Serial.print(valor_pwm);
  Serial.print("\n");

  delay(50);
}

