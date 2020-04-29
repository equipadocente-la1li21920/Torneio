# Torneio

## Como se usa?

Para criar um jogo escreve-se ./jogo.sh jogador1 jogador2

* Esta script vai criar um jogo entre estes dois jogadores
* Ela verifica se as jogadas são válidas e se o jogador utilizou menos de 2 segundos de CPU para jogar

Para criar um campeonato, é necessário:

* Escrever make preparar para criar a pasta do campeonato
* copiar os logotipos para a pasta campeonato/logos
* copiar os executáveis dos bots para a pasta campeonato/concorrentes

Para cada concorrente deve-se:
* decidir o nome que ele tem (e.g., la1pl2g03)
* criar o logotipo, que deve ser um png com 40x40 píxeis
* copiar o executável com esse nome para campeonato/concorrentes
* copiar o logotipo com o mesmo nome e a extensão png para a pasta campeonato/logos (e.g., la1pl2g03.png)
