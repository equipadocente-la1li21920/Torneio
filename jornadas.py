#!/usr/bin/env python3



import glob, os, random
concorrentes = {os.path.basename(f) for f in glob.glob('concorrentes/*')}
concorrentes = sorted(concorrentes)

num_jornadas = 2 * (len(concorrentes) - 1)
jogos = {}
jornadas = {J : set() for J in range(1, num_jornadas + 1)}
jogou = {J : {} for J in range(1, num_jornadas)}

possiveis = {f'{c1}:{c2}' for c1 in concorrentes for c2 in concorrentes if c1 != c2}

for J in range(1, num_jornadas + 1):
    escolhidos = set()
    while len(escolhidos) < len(concorrentes) // 2:
        poss = list(possiveis)
        escolhidos = set()
        for i in range(len(concorrentes) // 2):
            if len(poss) > 0:
                game = random.choice(poss)
                c1, c2 = game.split(':')
                escolhidos.add(game)
                poss = [x for x in poss if c1 not in x and c2 not in x]
    possiveis = possiveis - escolhidos
    for game in escolhidos:
        c1, c2 = game.split(':')
        jornadas[J].add((c1, c2))


    """
    for c1, c2 in zip(concorrentes, concorrentes[J:] + concorrentes[:J]):
        if c1 != c2 and f'{c1}{c2}' not in jogos and c1 not in jogou[J] and c2 not in jogou[J]:
            jogos[f'{c1}{c2}'] = J
            jornadas[J].add((c1, c2))
            jogou[J][c1] = True
            jogou[J][c2] = True
"""
    for jogo in sorted(jornadas[J]):
        print(f'{J:02}', *jogo)
