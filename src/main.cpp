/*
erro = valor_ref - valor_nivel
pwm = erro * kp
comentada e função "desligar bomba" uma vez que com o erro tendendo a zero o valor 
do pwm também tende a zero, ou seja, potência muito baixa ou nula
*/

#include <Arduino.h>

# define pinSensorTrig 8
# define pinSensorEcho 7
# define pinBomba 11
# define altura 23.6
# define vsom 0.0343
# define nivel_max 15.00
# define vazao 0.0513
# define kp 34.00

bool atraso = true;
bool cabecalho;
float time_now;
double distancia;
double nivel;
double valor_ref;

void ligarBomba(int valor_pwm)
{
  analogWrite(pinBomba, valor_pwm);
}

int definirPwm(double valor_nivel)
{  
  int pwm = (valor_ref - valor_nivel) * kp;

  if (pwm > 255) pwm = 255;
  else if (pwm < 0) pwm = 0;

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
}

void loop()
{  
  time_now = millis() / 1000;

  digitalWrite(pinSensorTrig, HIGH);
  delayMicroseconds(15);
  digitalWrite(pinSensorTrig, LOW);

  distancia = (vsom * pulseIn(pinSensorEcho, HIGH))/2;  
  nivel = altura - distancia;  

  /*if (nivel < nivel_max) ligarBomba(definirPwm(nivel));
  //else desligarBomba();*/

  ligarBomba(definirPwm(nivel));

  if (cabecalho == 1){
    Serial.print("tempo;nivel\n");
    cabecalho = 0;
  }
  
  Serial.print(time_now);
  Serial.print(";");
  Serial.println(nivel);
  Serial.print("\n");
}

