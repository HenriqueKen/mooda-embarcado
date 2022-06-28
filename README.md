***

<p align="center">
   <img src="https://i.ibb.co/XYbxkCj/mooda-logo.png" alt="mooda-logo" width=1000 />
</p>

<br />

<p align="center">  
  <a href="https://platformio.org/">
    <img src="https://img.shields.io/badge/Cpp-00599C?style=for-the-badge&logo=cplusplus&logoColor=ffffff" alt="cpp-badge" />
  </a>
  <a href="https://github.com/gvmossato/mooda/blob/main/LICENSE">
    <img src="https://img.shields.io/github/license/gvmossato/mooda?color=blue&style=for-the-badge" alt="license-badge" />
  </a>
</p>

***

<p align="center">
  <a href="#-sobre">📚 Sobre</a> |
  <a href="#-versões">🚢 Embarcado</a> |
  <a href="#-versões">⌛ Versões</a>
</p>

<p align="center">
  <b>Mooda</b> é o sistema de monitoramento que traduz em sentimentos as condições da sua mudinha! 
</p>
  
<h4 align="center">
  :star: Curtiu? Deixe uma estrela! :star:
</h4>

## 📚 Sobre

A Mooda é um sistema de monitoramento composto por duas partes:

1. Um sistema embarcado que deve ser colocado no vaso da própria planta, responsável por medir a temperatura, luminosidade, umidade do solo e outros, fornecendo um *feedback* em tempo real das condições dessa planta.

2. Uma plataforma online que recebe os dados do sistema embarcado por Wi-Fi e fornece uma visão histórica com totalizações das amostras coletadas, que pode ser conferida ao [clicar aqui](https://github.com/gvmossato/mooda).

Nesse repositório, encontram-se as particularidades do sistema embarcado.

## 🚢 Embarcado

<p align="center">
   Abaixo, o sistema embarcado em uma <i>Echeveria pulidonis</i>.
</p>

<p align="center">
   <img src="https://i.ibb.co/pL2cDT9/plant.jpg" alt="plant" width="400px" />
</p>
 
## ⌛ Versões

Durante a execução do projeto foram desenvolvidas diversas versões do código com e sem RTOS, em vias de testar suas aplicações e funcionalidades. Estas versões podem ser conferidas dentro da pasta `other_versions`.

`Mooda_1task_RTOS`: Versão da Mooda configurada com RTOS e apenas uma task.

`Mooda_2task_RTOS`: Versão da Mooda configurada com RTOS, duas tasks e XSemaphore.

`Mooda_StateMachine`: Versão da Mooda configurada sem RTOS, utilizando a função *millis()* e modelo de máquina de estados.
