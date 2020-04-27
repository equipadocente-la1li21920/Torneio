#!/usr/bin/python3

import glob, sys, os
from datauri import DataURI

tam = 20

def circle(L, C, color):
    raio = tam / 2.5
    X = tam * C + tam / 2
    Y = tam * L + tam / 2
    return vazia(L, C) + f'<circle cx="{X}" cy="{Y}" r="{raio}" stroke="black" stroke-width="1" fill="{color}" />'

def branca(L, C):
    return circle(L, C, "white")

def preta(L, C):
    return circle(L, C, "black")

def vazia(L, C):
    X = tam * C
    Y = tam * L
    return f'<rect x="{X}" y="{Y}" width="{tam}" height="{tam}" stroke="black" stroke-width="2" fill="white"  />'

def um(L, C):
    X = tam * C + tam / 4
    Y = tam * L + 3 * tam / 4
    return vazia(L, C) + f'<text x="{X}" y="{Y}" fill="black" style="fill: none; stroke: #000000;  font-size: 20px;">1</text>'

def dois(L, C):
    X = tam * C + tam / 4
    Y = tam * L + 3 * tam / 4
    return vazia(L, C) + f'<text x="{X}" y="{Y}" fill="black" style="fill: none; stroke: #000000;  font-size: 20px;">2</text>'

subs = {'.' : vazia, '*' : branca, '#' : preta, '1' : um, '2' : dois}

def logo(name, X, Y, size, img, opacity, fout):
    print(f'<text x="{X + 10}" y="{Y}" fill="black" stroke="black" font-size="20px">{name}</text>', file = fout)
    print(f'<image xlink:href="{img}" x="{X + 30}" y="{Y + 20}" height="{size}" width="{size}" />', file = fout)
    print(f'<rect x="{X + 30}" y="{Y + 20}" width="{size}" height="{size}" fill="white" fill-opacity="{opacity}" />', file = fout)


def render(num, filename, player1, fst, player2, snd):
    with open(filename + ".svg", "w") as fout:
        with open(filename) as f:
            op1 = 0 if num % 2 == 0 else 0.5
            op2 = 0 if num % 2 == 1 else 0.5
            print(f'<svg  height="{10 * tam}" width="{18 * tam}">', file = fout)
            print(f'<rect height="{10 * tam}" width="{18 * tam}" fill="white" />', file = fout)

            logo(player1,        0, 2 * tam, 2 * tam, fst, op1, fout)
            logo(player2, 13 * tam, 2 * tam, 2 * tam, snd, op2, fout)

            for L, line in enumerate(f.readlines()[:8]):
                for C, val in enumerate(line.strip()):
                    print(subs[val](L + 1, 5 + C), file = fout)
            print('</svg>', file = fout)


if len(sys.argv) != 5:
    print(f'Usage: {sys.argv[0]} name_player1 name_player2 logo_player1 logo_player2')
else:
    pl1 = sys.argv[1]
    pl2 = sys.argv[2]
    fst = DataURI.from_file(sys.argv[3])
    snd = DataURI.from_file(sys.argv[4])
    for num, filename in enumerate(sorted(glob.glob('jogos/pos[0-9][0-9]'))):
        render(num, filename, pl1, fst, pl2, snd)
