# Torneio

## Como verificar se a submissão para o bot está correta?

* Copiar para a `/tmp` o zip da submissão
* Copiar para a `/tmp` a script `extrai.py`
* Abrir um terminal na `/tmp`
* Executar a script passando-lhe o nome do zip

Exemplo:

```
rui@rui-VirtualBox:~/Torneio$ cp la1PL1G11.zip /tmp
rui@rui-VirtualBox:~/Torneio$ cp extrai.py /tmp
rui@rui-VirtualBox:~/Torneio$ cp la1PL1G11.zip /tmp
rui@rui-VirtualBox:~/Torneio$ cp /tmp/extrai.py .
rui@rui-VirtualBox:~/Torneio$ vi README.md 
rui@rui-VirtualBox:~/Torneio$ cp la1PL1G11.zip /tmp
rui@rui-VirtualBox:~/Torneio$ cp extrai.py /tmp
rui@rui-VirtualBox:~/Torneio$ la1PL1G12.zip /tmp
rui@rui-VirtualBox:~/Torneio$ cd /tmp
rui@rui-VirtualBox:/tmp$ python3 extrai.py la1PL1G11.zip la1PL1G12.zip 
Curso: la1	Turno: 1	Grupo: 11	Warnings: NO	Ficheiros: ['/tmp/la1PL1G11/aleat.c', '/tmp/la1PL1G11/common.c']
Curso: la1	Turno: 1	Grupo: 12	Warnings: YES!	Ficheiros: ['/tmp/la1PL1G12/aleat.c', '/tmp/la1PL1G12/common.c']
```

Reparem que há duas submissões, a primeira tem warnings e a segunda não.

## Como se usa?

Problemas comuns:

* Há pessoas que estão com problemas a ler o tabuleiro inicial, vejam se é o vosso caso
* Se ao correr o jogo aparecer um __killed__, isso quer dizer que o vosso programa foi morto porque demorou mais do que 2 segundos de CPU na vossa máquina
* Sugiro que corram o vosso programa contra vários jogadores aleatórios
* Se o vosso programa estiver a perder contra os jogadores aleatórios, deve querer dizer que algo não está bem

Para criar um campeonato, é necessário:

* Escrever `make` para inicializar o campeonato
* copiar os logotipos para a pasta `campeonato/logos`
* copiar os executáveis dos bots para a pasta `campeonato/concorrentes`

Para cada concorrente deve-se:
* decidir o nome que ele tem (e.g., `la1pl2g03`)
* criar o logotipo, que deve ser um png com 40x40 píxeis
* copiar o executável com esse nome para `campeonato/concorrentes`
* copiar o logotipo com o mesmo nome e a extensão png para a pasta `campeonato/logos` (e.g., `la1pl2g03.png`)

Para correr o campeonato, basta ir para a pasta campeonato e escrever:

```
./torneio.sh
```

## Exemplo de utilização
```
$ git clone ...
$ cd Torneio
$ make
$ for i in {1..4}; do cp aleat campeonato/concorrentes/aleat0$i; done
$ cp path_para_o_bot campeonato/concorrentes
$ cd concorrentes
$ ./torneio.sh
```

O que a script imprime é uma linha por jogo:

```
$ ./torneio.sh 
a01 a02 END 2
a01 a03 END 1
a01 a04 END 2
a02 a01 END 2
a02 a03 END 2
a02 a04 END 2
a03 a01 END 1
a03 a02 END 2
a03 a04 END 2
a04 a01 END 2
a04 a02 END 2
a04 a03 END 1
```

A primeira linha por exemplo quer dizer que houve um jogo entre a01 e a02 em que a02 ganhou. O nome a seguir a END é 1 se ganhou o primeiro jogador e 2 é o segundo jogador.

## Criar um jogo
Para criar um jogo escreve-se `./jogo.sh jogador1 jogador2`

* Esta script vai criar um jogo entre estes dois jogadores
* Ela verifica se as jogadas são válidas e se o jogador utilizou menos de 2 segundos de CPU para jogar
