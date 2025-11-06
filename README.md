Tetris Stack: minha simulação da fila de peças futuras. Foquei em fila circular, structs e I/O simples pra ficar didático e redondinho.

Visão geral

A ideia é simular a fila de peças futuras do jogo. Cada peça tem um ** (um char entre **, **, **, **) e um ** único que cresce a cada geração. Começo com a fila cheia (capacidade fixa de 5) e deixo o menu com três ações: jogar (dequeue), inserir (enqueue) e sair. Toda ação imprime a fila no formato `` do início ao fim.


Fila circular com ** e **, reaproveitando espaço quando o fim “dá a volta”.

Struct `` pra representar a peça.

Funções separadas pra cada responsabilidade (gerar, enfileirar, desenfileirar, imprimir...).

Validações pra caso de fila cheia/vazia, com mensagens amigáveis.

Semente aleatória ligada ao tempo pra variar os tipos.

Exemplo de saída:

Confira a seguir seu estado:

Fila de peças
[T 0] [O 1] [L 2] [I 3] [I 4]
Tabela: Visualização da fila de peças.
Curadoria de TI.

Opções de ação:

Código  Ação
1       Jogar peça (dequeue)
2       Inserir nova peça (enqueue)
0       Sair
Tabela: Comandos disponíveis para manipular a fila de peças.
Curadoria de TI.
