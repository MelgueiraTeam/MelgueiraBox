#include <ESP8266WiFi.h>      // Biblioteca do ESP
#include "DHT.h"              // Biblioteca do DHT 

#define DHTPIN 0              //Definindo o pino de saida do DHT1
#define DHTTYPE DHT11         //Definindo o tipo do DHT1

#define DHT2PIN 2             //Definindo o pino de saida do DHT2
#define DHT2TYPE DHT11        //Definindo o tipo do DHT2

#define id_caixa 1            //Definindo o identificador da Caixa

DHT dht1(DHTPIN, DHTTYPE);    
DHT dht2(DHT2PIN, DHT2TYPE);  

const char* ssid      = "XXXXXXXX";         //Nome da Rede WIFI
const char* password  = "XXXXXXXX";         //Senha da Rede WIFI
const char* host      = "XXXXXXXX";         //Endereço do Servidor que esta rodando o Banco


void setup()
{
  Serial.begin(115200);

  Serial.println("DHT1 Ligou!");
  dht1.begin();

  Serial.println("DHT2 Ligou!");
  dht2.begin();

  //Conectando a rede Wifi
  Serial.println();
  Serial.println();
  Serial.print("Conectao ao WIFI: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  Serial.print("Conectando");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Endereço de IP: ");
  Serial.println(WiFi.localIP());
}

void loop()
{

  float temperature1 = dht1.readTemperature();
  
  float humidity1 = dht1.readHumidity();
  
  float temperature2 = dht2.readTemperature();
  
  float humidity2 = dht2.readHumidity();
  
  
  if (isnan(temperature1) || isnan(humidity1) || isnan(temperature2) || isnan(humidity2)) {
    
    Serial.println("Falha na leitura do DHT11");
    
  } else {
    
    Serial.print("Umidade Sensor1: ");
    Serial.print(humidity1);
    Serial.print(" %\t");
    Serial.print("Temperatura Sensor1: ");
    Serial.print(temperature1);
    Serial.println(" *C");
    
    
    Serial.print("Umidade Sensor2: ");
    Serial.print(humidity2);
    Serial.print(" %\t");
    Serial.print("Temperatura Sensor2: ");
    Serial.print(temperature2);
    Serial.println(" *C");
    delay(2500);
  }

  Serial.print("Conectando ao IP/Dominio: ");
  Serial.println(host);

  // Usando a classe WiFiClient para criar as conexões TCP
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("Conexão Falhou");
    return;
  }


   if (isnan(temperature1) || isnan(humidity1) || isnan(temperature2) || isnan(humidity2)) {
    
    Serial.println("Falha na leitura do DHT11");
    
  } else {
  

  // Isto vai enviar a requisição para o banco
  client.print(String("GET /connect.php?") +
               ("&temperatura_ninho=") + temperature1 +
               ("&umidade_ninho=") + humidity1 +
               ("&temperatura_melgueira=") + temperature2 +
               ("&umidade_melgueira=") + humidity2 +
               ("&id_caixa=") + id_caixa +
               " HTTP/1.1\r\n" +
               "Host: " + host + "\r\n" +
               "Connection: close\r\n\r\n");
  unsigned long timeout = millis();
  while (client.available() == 0) {
    if (millis() - timeout > 1000) {
      Serial.println(">>> Tempo Limite do Cliente excedido!");
      client.stop();
      return;
    }
  }

  // Le todas as linhas da resposta do servidor e printa no serial
  while (client.available()) {
    String line = client.readStringUntil('\r');
    Serial.print(line);
    }

  }
  

  Serial.println();
  Serial.println("Fechando Conexão");
  
}
