Este programa foi desenvolvido para controlar os LEDs e o buzzer de um **Raspberry Pi Pico W** de forma interativa. Ao ligar o sistema, ele aguarda um comando vindo do seu computador para começar a execução. Para isso, você precisará usar um terminal, como o **PuTTY**, que vai estabelecer a comunicação entre o computador e o Pico.

Quando o sistema estiver esperando por um comando, basta pressionar a tecla **Espaço** no terminal. Assim que isso acontecer, os LEDs vão começar a piscar em sequência: primeiro o **vermelho**, depois o **verde**, em seguida o **azul** e, por último, o LED **branco**. Cada cor ficará acesa por **2 segundos**. Após o LED branco, o **buzzer** será acionado e emitirá um som por **2 segundos**.

Assim que a sequência for concluída, o sistema vai aguardar novamente que você pressione a tecla **Espaço** para reiniciar o ciclo e começar tudo de novo. Ou seja, toda vez que você apertar a tecla **Espaço**, os LEDs vão trocar de cor e o buzzer será acionado.

Este programa funciona com uma comunicação simples entre o Raspberry Pi Pico W e o terminal, utilizando a interface **UART** a uma taxa de **9600 baud**. Para interromper o processo, basta fechar o terminal ou desconectar o Pico do computador. 

É uma maneira divertida e fácil de interagir com os LEDs e buzzer do Raspberry Pi Pico W, e também um excelente exercício para testar o controle de periféricos em sistemas embarcados.

Link do vídeo: https://www.dropbox.com/scl/fi/1jdj6453j3trvr89hsotu/video-atividade-2-uart-1-1.mp4?rlkey=33obrciytmjquqlr01losuvcx&st=48fzohee&dl=0