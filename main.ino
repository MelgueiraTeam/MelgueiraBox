#include "DHT.h" //Importando biblioteca do sensor DHT11.

#define DHTPIN A1 //Definindo o pino para dados do DHT11.
#define DHTTYPE DHT11 //Definindo que o modelo do sensor DHT sera o 11.

#define MaxBee 32 //Definindo valor maximo de temperatura para as abelhas.
#define MinBee 25 //Definindo o valor minimo de temperatura para as abelhas.

DHT dht(DHTPIN, DHTTYPE); //Atribuindo os parametros para a função referente ao DHT.

void setup(){

    Serial.begin(9600); //Inicia o monitor serial do arduino com um baud rate de 9600 bits por segundo para o DHT11.

    dht.begin(); //Inicia a comunicação com o sensor DHT11.

    Serial.println("DHT11 Iniciou!"); 
}

void loop(){

    float u = dht.readHumidity(); //Atribuindo o valor da umidade do sensor DHT11 na variavel u.
    float t = dht.readTemperature(); //Atribuindo o valor da temperatura do sensor DHT11 na variavel t.

    if(isnan(u) ||  isnan(t)) { //Realizando testes de verificação dos valores do Sensor DHT11.

        Serial.println("Erro na leitura do Sensor DHT11");

    } else { //Caso não ocorrer erros na leitura dos dados 

        Serial.print("Temperatura: ");
        Serial.print(t);  //Apresentando dados da temperatura no Monitor serial.
        Serial.print("°C\t");

        Serial.print("Umidade: ");
        Serial.print(u);  //Apresentando dados da umidade no Monitor serial.
        Serial.println("%");
        delay(1000);

        if(t<MinBee){

            //Adicionar instruções de Controle.

        } else if(t>MaxBee){

            //Adicionar instruções de Controle.

        }

    }
}