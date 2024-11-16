// Carregando as bibliotecas
#include <WiFi.h> //Habilita comunicação do ESP32 com WI-FI
#include <PubSubClient.h> // Protocolo de comunicação MQTT IoT
#include <HTTPClient.h> //Faz a comunicação com o serviço de mensagens "mosquito.org"

unsigned long sensor = 32; //Porta analógica do sensor de gás que recebe de 0v a 5v

//Variáveis para os GPIO digitais
byte verde1 = 15;
byte verde2 = 2;
byte amarelo1 = 4;
byte amarelo2 = 5;
byte vermelho1 = 18;
byte vermelho2 = 19;
byte ledwifi = 21;
byte exaustor = 22;
byte buzzer = 23;

// Variáveis para as condicionais
int sen = 0;
byte if1 = 0;
byte if2 = 0;
byte if3 = 0;
byte if4 = 0;
// Variáveis para WI-FI
const char* ssid = "GUSSONI";
const char* password = "Zeg142011";
const char* mqtt_server = "test.mosquitto.org";
const char* api_key = "2684544"; // Chave API do CallMeBot
const char* numero = "+5511983270585"; // Número de WhatsApp

// Instancia a classe WiFiClient para conectar a rede Wi-Fi.
WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    delay(10);
    Serial.print("Conectando no WI-FI ");
    Serial.println(ssid);
    enviarMensagemWhatsApp();  //Mensagem após conexão
  
    Serial.println("WiFi conectado.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  
    // Configurar o servidor MQTT
    client.setServer(mqtt_server, 1883);
    
    // Configura os GPIO para "I ou O".
    pinMode(sensor, INPUT);
    pinMode(verde1, OUTPUT); 
    pinMode(verde2, OUTPUT); 
    pinMode(amarelo1, OUTPUT); 
    pinMode(amarelo2, OUTPUT); 
    pinMode(vermelho1, OUTPUT); 
    pinMode(vermelho2, OUTPUT); 
  //  pinMode(ledd, OUTPUT);
    pinMode(exaustor, OUTPUT);
    pinMode(ledwifi, OUTPUT); // LED WI-FI
     pinMode(buzzer, OUTPUT); 
}

void enviarMensagemWhatsApp() {
    if (WiFi.status() == WL_CONNECTED) {
        HTTPClient http;

        // Formata mensagem para a URL da API
        String mensagem = "ESP32%20conectado%20ao%20Wi-Fi";
        String url = "https://api.callmebot.com/whatsapp.php?phone=" + String(numero) + "&text=" + mensagem + "&apikey=" + String(api_key);

        http.begin(url);
        
        int httpResponseCode = http.GET(); // Enviar requisição GET

        if (httpResponseCode > 0) {
            String response = http.getString();
            Serial.println(httpResponseCode);
            Serial.println(response);
            Serial.println("Mensagem enviada com sucesso...");
        } else {
            Serial.print("Erro ao enviar a mensagem. Código HTTP: ");
            Serial.println(httpResponseCode);
        }

        http.end();
    }
}

// Condicional para WI-FI
void ST_conexao() {
    if (WiFi.status() == WL_CONNECTED) {
        digitalWrite(ledwifi, HIGH);
        delay(150);
        digitalWrite(ledwifi, LOW);
        delay(150);
    } else {
        digitalWrite(ledwifi, LOW);
    }
}

void loop() {
    ST_conexao();
    sen = map(analogRead(sensor), 0, 4095, 0, 1023);
    
    // Todos os LEDs desligados
    if (sen < 300) {
    
        digitalWrite(verde1, LOW);
        digitalWrite(verde2, LOW);
        digitalWrite(amarelo1, LOW);
        digitalWrite(amarelo2, LOW);
        digitalWrite(vermelho1, LOW);
        digitalWrite(vermelho2, LOW);
    }
    // LED verde1 aceso
    else if (sen > 310 && sen < 400) {
        digitalWrite(verde1, HIGH);
        digitalWrite(verde2, LOW);
        digitalWrite(amarelo1, LOW);
        digitalWrite(amarelo2, LOW);
        digitalWrite(vermelho1, LOW);
        digitalWrite(vermelho2, LOW);
    }
    // LEDs verde1 e verde2 acesos
    else if (sen > 410 && sen < 450) {
        digitalWrite(verde1, HIGH);
        digitalWrite(verde2, HIGH); //Após acionamento do exautor e normalização do nível, envia "Nível de GÁS normal".
        digitalWrite(amarelo1, LOW);
        digitalWrite(amarelo2, LOW);
        digitalWrite(vermelho1, LOW);
        digitalWrite(vermelho2, LOW);
    }
    // LEDs verde1, verde2 e amarelo1 acesos
    else if (sen > 460 && sen < 600) {
        digitalWrite(verde1, HIGH);
        digitalWrite(verde2, HIGH);
        digitalWrite(amarelo1, HIGH); //"Detectado GÁS no Sitema"
        digitalWrite(amarelo2, LOW);
        digitalWrite(vermelho1, LOW);
        digitalWrite(vermelho2, LOW);
    }
    // LEDs verde1, verde2, amarelo1 e amarelo2 acesos
    else if (sen > 610 && sen < 750) {
        digitalWrite(verde1, HIGH);
        digitalWrite(verde2, HIGH);
        digitalWrite(amarelo1, HIGH);
        digitalWrite(amarelo2, HIGH);
        digitalWrite(vermelho1, LOW);
        digitalWrite(vermelho2, LOW);
    }
    // LEDs verde1, verde2, amarelo1, amarelo2 e vermelho1 acesos
    else if (sen > 760 && sen < 900) {
        digitalWrite(verde1, HIGH);
        digitalWrite(verde2, HIGH);
        digitalWrite(amarelo1, HIGH);
        digitalWrite(amarelo2, HIGH);
        digitalWrite(vermelho1, HIGH); //"Nível de GÁS crítico. Acionando o exaustor"
        digitalWrite(vermelho2, LOW);
    }
    // Todos os LEDs acesos
    else if (sen > 950) {
        digitalWrite(verde1, HIGH);
        digitalWrite(verde2, HIGH);
        digitalWrite(amarelo1, HIGH);
        digitalWrite(amarelo2, HIGH);
        digitalWrite(vermelho1, HIGH);
        digitalWrite(vermelho2, HIGH);//Sinal sonoro para emergencia. "Evacuar Local"
    }

    // Lógica para enviar mensagens via WhatsApp
    if (sen > 460 && if1 == 0) {
        HTTPClient http;

        // Formatar a URL da API
        String mensagem = "Detectado%20GÁS%20no%20Sistema"; // Mensagem formatada para URL
        String url = "https://api.callmebot.com/whatsapp.php?phone=" + String(numero) + "&text=" + mensagem + "&apikey=" + String(api_key);

        http.begin(url);
        
        int httpResponseCode = http.GET(); // Enviar requisição GET

        if (httpResponseCode > 0) {
            String response = http.getString();
            Serial.println("Detectado GÁS no sistema");
        } else {
            Serial.print("Erro ao enviar a mensagem. Código HTTP: ");
            Serial.println(httpResponseCode);
        }

        http.end();

        if1 = 1;
        if2 = 1;
    }

    if (sen < 450 && if2 == 1) {
        HTTPClient http;

        // Formatar a URL da API
        String mensagem = "Nível%20de%20gás%20normal"; // Mensagem formatada para URL
        String url = "https://api.callmebot.com/whatsapp.php?phone=" + String(numero) + "&text=" + mensagem + "&apikey=" + String(api_key);

        http.begin(url);
        
        int httpResponseCode = http.GET(); // Enviar requisição GET

        if (httpResponseCode > 0) {
            String response = http.getString();
            Serial.println("Nível de GÁS normal");
        } else {
            Serial.print("Erro ao enviar a mensagem. Código HTTP: ");
            Serial.println(httpResponseCode);
        

        http.end();
       
    }
     if2 = 0;
        if1 = 0;
        if3 = 0;
    }

    if (sen > 760 && if3 == 0) {
        HTTPClient http;

        // Formatar a URL da API
        String mensagem = "Nível%20de%20GÁS%20crítico.%20Acionando%20o%20exaustor"; // Mensagem formatada para URL
        String url = "https://api.callmebot.com/whatsapp.php?phone=" + String(numero) + "&text=" + mensagem + "&apikey=" + String(api_key);

        http.begin(url);
        
        int httpResponseCode = http.GET(); // Enviar requisição GET

        if (httpResponseCode > 0) {
            String response = http.getString();
            Serial.println("Nível de GÁS crítico. Acionando o exaustor");
        } else {
            Serial.print("Erro ao enviar a mensagem. Código HTTP: ");
           Serial.println(httpResponseCode);
     }
    
     http.end();

        digitalWrite(exaustor, HIGH);
    
        delay(5000);
        digitalWrite(exaustor, LOW);
        if3 = 1;
        if4 = 0;
    }

    if(sen > 950){
      digitalWrite(buzzer, HIGH);
      delay(5000);
      digitalWrite(buzzer, LOW);
      delay(5000);
    }
}
