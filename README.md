# Projeto Embarcados

Desenvolvendo um controle remoto.

## Entrega 1

### Integrantes

- Bruna Lima Meinberg
- Luana Wilner Abramoff

### Ideia

A ideia gira entorno de construir um software + controle  que sempre ganha de você no jokempô

### Nome

Jokembot

### Usuários 

Qualquer um que queira jogar! Mas pode ser que as crianças se interessem mais!

### Software/Jogo 

Uma interface de pygame, onde a partir da detecção dos movimentos, é transmitida para o usuário a resposta da robô

### Jornada do usuários (3 pts)

Joãzinho chega da escola muito triste, pois seu pai está corrigindo provas Intermediárias de seus alunos. Ele gostaria muito de jogar jokempô com seu pai, mas neste momento não é possível. Então, ele aloca o sensor muscular em seu antebraço, e abre o jogo, que será na plataforma Pygame. Um led alocado à protoboard irá sinalizar quando o sensor estiver conectado via bluetooth à interface.  Antes de começar a jornada, o jogo solicita à Joãozinho que ele faça rodadas testes, simulando os três movimentos do jokempô: Pedra, papel e tesoura. Assim o software consegue reconhecer os movimentos do usuário. Ao acabar o reconhecimento, Joãozinho digita o número de rodadas que deseja jogar no teclado matricial, e aperta o botão para dar ínicio. O jogo irá sinalizar o começo também com uma contagem regressiva, e após 10 segundos, a interface mostra qual foi o movimento do bot e qual foi o movimento de Joãozinho, identificado pelo sensor. A pontuação será contada, e o jogador será identificado na tela. Após três partidas se Joãozinho tiver perdido, um vibrador que estará junto ao sensor alocado ao corpo, irá vibrar fortemente, sinalizando a derrota. Assim começará uma nova partida, de acordo com a quantidade de partidas informadas pelo teclado matricial. 

Mariazinha é estudante e quando não esta se preparando para o vestibular de engenharia elétrica gosta de se divertir com projetos que envolvam programação e hardware, por isso gosta de passar seu tempo jogando jokempô com um robo. Por isso, no seu tempo livre, vai ao laboratório de informática, aloca o sensor muscular em seu braço e, por alguns minutos, se diverte com o software. Costuma jogar por 20 rodadas e a parte que mais a chama atenção é a que está na protoboard, pois se interessa muito pelas possíveis conexões. Se pergunta como é possível o led e aquilo que está na tela do computador estão sincronizados e na rapidez em que tudo acontece.

### Comandos/ Feedbacks (2 pts)

-> Botão de início: começar o jogo
-> Led 1: início do jogo 
-> Led 2: derrota/vitória
-> Vibração: derrota
-> Sensor muscular: enviara os dados relacionados a quais dedos da mão estarão levantados
-> Computador: adversário

## In/OUT (3 pts)

> Sensor muscular: entrada
-> Botão de início: entrada
-> Leds de aviso: saída
-> Vibração: saída
-> Teclado Matricial: entrada (quantas vezes quer jogar)

### Design (2 pts)


![image](https://github.com/insper-classroom/23b-emb-proj-jokembot/assets/91220404/01d6b4f9-62df-44b6-a5e8-6a0d93ff9947)

