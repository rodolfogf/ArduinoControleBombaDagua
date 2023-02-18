/*
os valores de kp, ki e kd foram os sugeridos pelo Marcos
*/

#include <Arduino.h>

# define pinSensorTrig 8
# define pinSensorEcho 7
# define pinBomba 11
# define altura 24.00
# define vsom 0.0343
# define nivel_max 15.00
# define kp 80.00
# define ki 0.1
# define kd 35.00

bool cabecalho;
unsigned long tempo_agora;
unsigned long tempo_antes;
unsigned long tempo_segundos;
double distancia;
double nivel;
double valor_ref;
double erro_previo;
double erro_atual;
double erro_acumulado;
unsigned long  atraso_inicio;

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
  erro_somatorio = erro_atual * (tempo_agora - tempo_antes)/1000.00 + erro_somatorio;

  //é uma aproximação da derivada
  double derivada_aprox = (erro_atual - erro_anterior)/(tempo_agora - tempo_antes)/1000.00;

  int pwm = erro_atual * kp + (ki * erro_somatorio) + kd * derivada_aprox;

  //o valor do pwm não pode ser menor que 0 nem maior que 255
  if (pwm > 255) pwm = 255;
  else if (pwm < 0) pwm = 0;

  /*na próxima iteração o valor atual de tempo será o valor anterior de tempo
  o mesmo raciocínio serve para o erro*/
  tempo_antes = tempo_agora;
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
  tempo_antes = 0;
  erro_previo = 0;
  atraso_inicio = 10000;
}

void loop()
{  
  tempo_agora = millis();
  tempo_segundos = tempo_agora/1000;

  if (tempo_agora > atraso_inicio){

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
      Serial.print("tempo;nivel;pwm\n");
      cabecalho = 0;
    }

    Serial.print(tempo_segundos);
    Serial.print(";");
    Serial.print(nivel);
    Serial.print(";");
    Serial.print(valor_pwm);
    Serial.print("\n");

    //Utilizado para corrigir os valores discrepantes que estavam sendo impressos no gráfico
    delay(50);
  }  
}