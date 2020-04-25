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

def render(num, filename, fst, snd):
    with open(filename + ".svg", "w") as fout:
        with open(filename) as f:
            op1 = 0 if num % 2 == 0 else 0.5
            op2 = 0 if num % 2 == 1 else 0.5
            print(num, op1, op2)
            print(f'<svg height="{8 * tam}" width="{18 * tam}">', file = fout)

            print(f'<image xlink:href="{fst}" x="0" y="{3 * tam}" height="{4 * tam}" width="{4 * tam}" />', file = fout)
            print(f'<rect x="0" y="{3 * tam}" width="{4 * tam}" height="{4 * tam}" fill="white" fill-opacity="{op1}" />', file = fout)

            print(f'<image xlink:href="{snd}" x="{13 * tam}" y="{3 * tam}" height="{4 * tam}" width="{4 * tam}" />', file = fout)
            print(f'<rect x="{13 * tam}" y="{3 * tam}" width="{4 * tam}" height="{4 * tam}" fill="white" fill-opacity="{op2}" />', file = fout)

            for L, line in enumerate(f.readlines()[:8]):
                for C, val in enumerate(line.strip()):
                    print(subs[val](L, 5 + C), file = fout)
            print('</svg>', file = fout)


fst = DataURI.from_file(sys.argv[1])
snd = DataURI.from_file(sys.argv[2])
for num, filename in enumerate(sorted(glob.glob('pos[0-9][0-9]'))):
    render(num, filename, fst, snd)

os.system("rm jogo.mp4; ffmpeg -r 1 -i pos%02d.svg -pix_fmt yuv420p jogo.mp4")

