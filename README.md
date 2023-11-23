# Edge Computing | Global Solution 

# Objetivo
O propósito desta tarefa consiste no desenvolvimento de uma arquitetura para uma aplicação IoT capaz de receber e transmitir dados provenientes de dispositivos conectados.

# Resumo do projeto
O nosso projeto, intitulado "WebConnect", visa criar um software para aplicação móvel. Nele, os usuários podem cadastrar todo o seu histórico médico relevante, incluindo exames, e compartilhar essas informações com o profissional de saúde de sua escolha. Essa abordagem simplifica significativamente a transição da ficha médica de um paciente para um novo profissional, agilizando o processo de consulta e aprimorando o atendimento.

# Solução proposta para Edge Computing
Com o intuito de aplicar os conceitos aprendidos em IoT durante o curso de Edge Computing, propomos uma adaptação. Durante uma consulta online, a aferição de medidas vitais do paciente, como temperatura corporal, pressão sanguínea, batimento cardíaco ou oxigenação do sangue, torna-se desafiadora para o médico.
Considerando essa limitação, planejamos utilizar dispositivos como Smartwatches, que possuem o hardware apropriado para essas medições. Os dados seriam então transmitidos para o nosso software. Para ilustrar essa proposta no site Wokwi, optamos por utilizar o sensor DHT22, que realiza medições de temperatura e umidade. Interpretaremos esses dados como temperatura corporal e oxigenação, respectivamente.

# Instruções de uso 

- Vídeo explicativo: 
- Simulação: https://wokwi.com/projects/381660760030939137

- Para que o sistema funcione, é necessário montar o circuito com o ESP32, DTH22 e display, conforme o diagrama abaixo. Em seguida, carregue o código correspondente em sua memória.
- Para que o código funcione corretamente, é necessário instalar e declarar as seguintes bibliotecas no início do código:

```c
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "ArduinoJson.h"
#include "EspMQTTClient.h"
#include "DHTesp.h"
```

# Grupo
- André Lambert (RM99148)
- Vitor Maia (RM99658)

# Diagrama do circuito
![circuito](circuito.png)
