#include "DHT.h" //Importando biblioteca do sensor DHT11.

#define DHT1PIN 6 //Definindo o pino para dados do DHT11.
#define DHT2PIN 7 //Definindo o pino para dados do DHT11.

#define DHTTYPE DHT11 //Definindo que o modelo do sensor DHT sera o 11.

#define MaxTempBee 32 //Definindo valor maximo de temperatura para as abelhas.
#define MinTempBee 24 //Definindo o valor minimo de temperatura para as abelhas.

#define MaxHumBee 60  //Definindo valor maximo de umidade para as abelhas.
#define MinHumBee 50  //Definindo o valor minimo de umidade para as abelhas.

DHT dht1(DHT1PIN, DHTTYPE); //Atribuindo os parametros para a função referente ao DHT.
DHT dht2(DHT2PIN, DHTTYPE); //Atribuindo os parametros para a função referente ao DHT.


#define IN4 4 //Definindo os pinos de saida pra Ponte H;
#define IN5 5 //Definindo os pinos de saida pra Ponte H;


void setup() {

  Serial.begin(9600); //Inicia o monitor serial do arduino com um baud rate de 9600 bits por segundo para o DHT11.

  dht1.begin(); //Inicia a comunicação com o sensor DHT11.
  dht2.begin(); //Inicia a comunicação com o sensor DHT11.

  Serial.println("DHT11 Iniciou!");
  pinMode(IN4, OUTPUT);
  pinMode(IN5, OUTPUT);
}

void loop() {

  float u1 = dht1.readHumidity(); //Atribuindo o valor da umidade do sensor DHT11 na variavel u.
  float t1 = dht1.readTemperature(); //Atribuindo o valor da temperatura do sensor DHT11 na variavel t.

  float u2 = dht2.readHumidity(); //Atribuindo o valor da umidade do sensor DHT11 na variavel u.
  float t2 = dht2.readTemperature(); //Atribuindo o valor da temperatura do sensor DHT11 na variavel t.
  delay(2000);
  if (isnan(u1) ||  isnan(t1)) { //Realizando testes de verificação dos valores do Sensor DHT11.

    Serial.println("Erro na leitura do Sensor DHT11");

  } else { //Caso não ocorrer erros na leitura dos dados

    Serial.print("Sensor1 - Temperatura: ");
    Serial.print(t1);  //Apresentando dados da temperatura no Monitor serial.
    Serial.print("°C\t");

    Serial.print(" - Umidade: ");
    Serial.print(u1);  //Apresentando dados da umidade no Monitor serial.
    Serial.println("%");

    

    Serial.print("Sensor2 - Temperatura: ");
    Serial.print(t2);  //Apresentando dados da temperatura no Monitor serial.
    Serial.print("°C\t");

    Serial.print("  - Umidade: ");
    Serial.print(u2);  //Apresentando dados da umidade no Monitor serial.
    Serial.println("%");

    delay(2000);  //Delay de 3 segundo.
 

    // Continuamos
    if (t1 < MinTempBee) {

      //Adicionar instruções de Controle.
      Serial.println("Ligando Resistencia ");
      //Ligando resistencia
      digitalWrite(IN4, HIGH);
      digitalWrite(IN5, LOW);
      delay(15000); // 2 segundos
      Serial.println("Desligando Resistencia ");
      //Desligando a resistencia
      digitalWrite(IN4, HIGH);
      digitalWrite(IN5, HIGH);
      delay(2500);

    } else if (t1 > MaxTempBee) {

      //Adicionar instruções de Controle.

    }

    if (u1 < MinHumBee) {

      //Adicionar instruções de Controle.

    } else if (u1 > MaxHumBee) {

      //Adicionar instruções de Controle.

    }

  }
}
