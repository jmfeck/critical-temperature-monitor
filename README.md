# Monitor de Temperatura Crítica

**Nota:** Este projeto foi desenvolvido como parte de um trabalho acadêmico universitário em 2015/2016.  
Está sendo arquivado aqui para fins históricos e de portfólio.

> ⚡ Importante: A documentação e os comentários no código foram traduzidos para inglês para acessibilidade internacional.

## Descrição do Projeto

Este projeto implementa um sistema de monitoramento de temperatura crítica utilizando:

- Arduino Mega 2560
- Shield Ethernet
- Sensor de Temperatura (conectado no pino A0)
- Display LCD 16x2
- Botões de controle (aumentar, diminuir e ativar monitoramento)
- LEDs de indicação de estado

O sistema permite que o usuário ajuste a temperatura crítica (`tempSet`) diretamente nos botões físicos.  
Quando a temperatura medida (`tempData`) ultrapassa esse valor, um alerta é disparado:

- Um alerta é enviado por e-mail e notificação push.
- Uma linha é automaticamente registrada em uma planilha Google Sheets.

Estas ações são gerenciadas através do serviço gratuito **PushingBox**, que recebia requisições HTTP do Arduino e repassava via HTTPS para os serviços de destino.

> ⚠️ Observação: O Arduino Mega 2560 com Ethernet Shield da época não suportava conexões HTTPS. O PushingBox era utilizado como um intermediário para fazer a ponte segura.

> ⚠️ Nota adicional: O serviço PushingBox pode não estar mais ativo. Para replicar o projeto hoje, recomenda-se usar alternativas como:
> - Webhooks próprios
> - Integrações via IFTTT
> - Integrações diretas com bancos de dados

Este projeto foi uma **prova de conceito**, focado em integrar hardware simples com serviços em nuvem gratuitos para monitoramento em tempo real.

## Hardware Utilizado

- Arduino Mega 2560
- Shield Ethernet
- Sensor de Temperatura (ex.: LM35)
- Display LCD 16x2 (conectado nos pinos 33–43)
- Botões físicos
- LEDs indicadores
- Cabos e Protoboard
- Conexão de Internet (via cabo)

## Estrutura do Projeto

- `src/` — Código principal do projeto (`critical_temperature_monitor.ino`)
- `extras/` — Códigos antigos e versões de testes (não incluídos na recuperação atual)
- `docs/` — Documentos do projeto (proposta, relatório final, apresentação, esquemáticos)
- `images/` — Fotos do hardware e capturas de tela

## Como Rodar

1. Abra o arquivo `critical_temperature_monitor.ino` na IDE Arduino.
2. Ajuste o seu `DeviceID` do PushingBox no código (procure `YOUR_DEVICE_ID`).
3. Faça upload do código para o Arduino Mega.
4. Conecte o Arduino à internet usando o Shield Ethernet.
5. Ajuste a temperatura crítica nos botões físicos (`+` e `-`).
6. Pressione o botão OK para ativar o monitoramento.

Quando a temperatura ultrapassar o valor ajustado, o sistema enviará automaticamente o alerta.

## Requisitos

- Arduino IDE (versão compatível com Arduino Mega 2560)
- Shield Ethernet funcional
- Conta no PushingBox (ou serviço alternativo)
- Rede com acesso à Internet

---

Projeto arquivado preservando seu conteúdo e propósito original.
