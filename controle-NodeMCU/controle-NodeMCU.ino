#include <ESP8266WiFi.h>

const char *ssid = "";     //VARIÁVEL QUE ARMAZENA O NOME DA REDE SEM FIO EM QUE VAI CONECTAR
const char *password = ""; //VARIÁVEL QUE ARMAZENA A SENHA DA REDE SEM FIO EM QUE VAI CONECTAR

WiFiServer server(8070);

void setup()
{
  Serial.begin(115200);
  delay(10);

  Serial.println("");
  Serial.print("Conectando a ");
  Serial.print(ssid); //ESCREVE O NOME DA REDE NA SERIAL
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(16, OUTPUT);
  digitalWrite(LED_BUILTIN, 1);
  WiFi.begin(ssid, password); //PASSA OS PARÂMETROS PARA A FUNÇÃO QUE VAI FAZER A CONEXÃO COM A REDE SEM FIO

  while (WiFi.status() != WL_CONNECTED)
  { //ENQUANTO STATUS FOR DIFERENTE DE CONECTADO
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Conectado a rede sem fio ");
  Serial.println(ssid); //ESCREVE O NOME DA REDE NA SERIAL
  server.begin();       //INICIA O SERVIDOR PARA RECEBER DADOS NA PORTA DEFINIDA EM "WiFiServer server(porta);"
  Serial.println("Servidor iniciado");

  Serial.print("IP para se conectar ao NodeMCU: ");
  Serial.print("http://");
  Serial.println(WiFi.localIP()); //ESCREVE NA SERIAL O IP RECEBIDO DENTRO DA REDE SEM FIO
  digitalWrite(16, 0);
}
void loop()
{
  WiFiClient client = server.available(); //VERIFICA SE ALGUM CLIENTE ESTÁ CONECTADO NO SERVIDOR
  if (!client)
  {         //SE NÃO EXISTIR CLIENTE CONECTADO, FAZ
    return; //REEXECUTA O PROCESSO ATÉ QUE ALGUM CLIENTE SE CONECTE AO SERVIDOR
  }
  Serial.println("Novo cliente se conectou!");
  while (!client.available())
  { //ENQUANTO CLIENTE ESTIVER CONECTADO
    delay(1);
  }
  String request = client.readStringUntil('\r'); //FAZ A LEITURA DA PRIMEIRA LINHA DA REQUISIÇÃO
  Serial.println(request);                       //ESCREVE A REQUISIÇÃO NA SERIAL
  client.flush();                                //AGUARDA ATÉ QUE TODOS OS DADOS DE SAÍDA SEJAM ENVIADOS AO CLIENTE
  //************************************************
  sentido_motor_esquerda = request.substring(0, 1);
  velocidade_motor_esquerda = request.substring(1, 4);

  sentido_motor_direita = request.substring(4, 5);
  velocidade_motor_direita = request.substring(5);

  if (sentido_motor_esquerda == "+")
  {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    digitalWrite(ENA, velocidade_motor_esquerda);
  }
  else if (sentido_motor_esquerda == "-")
  {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    digitalWrite(ENA, velocidade_motor_esquerda);
  }

  if (velocidade_motor_direita == "+")
  {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    digitalWrite(ENA, velocidade_motor_direita);
  }
  else if (velocidade_motor_direita == "-")
  {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    digitalWrite(ENA, velocidade_motor_direita);
  }

  if (request.indexOf("led5_off") != -1)
  {
    digitalWrite(LED_BUILTIN, 1);
  }
  else if (request.indexOf("led5_on") != -1)
  {
    digitalWrite(LED_BUILTIN, 0);
  }

  //************************************************
  client.println("<html>");
  client.println("<h1><center>Controrle Remoto</center></h1>");
  client.println("<center><font size='5'>Teste de controle sem fio por rede wirelesss</center>");
  client.println("</html>");
  //************************************************
  delay(1);
  Serial.println("Cliente desconectado");
  Serial.println("");
}
