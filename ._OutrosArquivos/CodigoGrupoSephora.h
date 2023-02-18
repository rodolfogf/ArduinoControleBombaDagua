int pino_trigger = 7;
int pino_echo = 6;
int pino_pwm = 3;
int pwm = 150;
int ponto_medicao = A2;
float altura = 0;
//int ponto_entrada_tensao = A0;
int valor = 0;
int cont = 0;
float media = 0;
float ref = 10.0;
float erroAtual = 0.0;
float ultimoErro = 0.0;
float dErro = 0.0;
float somatorioErro = 0.0;
float kp = 5.562004357; //40 - antigo valor
float ki = 0.007491491;
float kd = 33.371195;
//80 min
//150 max
unsigned long ultimoTempo = millis();

float duracao_us, distancia_cm, nivel_agua_cm;
  
void setup()
{
  Serial.begin(9600);
  pinMode(4, OUTPUT);
  pinMode(5, INPUT);
  pinMode(pino_pwm, OUTPUT);
}

void loop()
{
    if (Serial.available()) {
    // lê do buffer o dado recebido:
    pwm = Serial.parseInt();
    analogWrite(pino_pwm, pwm);
       Serial.print("PWM");
          Serial.print(pwm);


  }

  Serial.println(pwm);

  digitalWrite(pino_trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(pino_trigger, LOW);
  duracao_us = pulseIn(pino_echo, HIGH);
  distancia_cm = 0.017 * duracao_us;
  nivel_agua_cm = 19 - distancia_cm;
 // Serial.print("Tensão PWM ");
 // Serial.print("Distancia: ");
 // Serial.print(distancia_cm);
 // Serial.println("cm");
//  Serial.print("Nível da água em cm: ");
   Serial.print(nivel_agua_cm);

// Serial.print(erroAtual);
  //Serial.print("\n");

   erroAtual = ref - nivel_agua_cm;
   somatorioErro = (erroAtual * (millis()-ultimoTempo)+ somatorioErro);
   dErro = (erroAtual - ultimoErro)/(millis()-ultimoTempo);
  // pwm =erroAtual*kp+(ki*somatorioErro)+kd*dErro;
   if(pwm >= 255){
    pwm = 255;
   } else if (pwm <0){
    pwm = 0;
   }
   Serial.print(pwm);
   analogWrite(pino_pwm, pwm);
   Serial.print(",");
   Serial.print(millis() - ultimoTempo);
   ultimoTempo = millis();
   ultimoErro = erroAtual;

   // Serial.print("Tempo: ");

   
   
 
 // Serial.println("cm");
  delay(200);