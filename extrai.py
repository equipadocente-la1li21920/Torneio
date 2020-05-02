import sys, os, re, subprocess, glob

def extrai(filename):
    m = re.match(r'((li2|la1)PL([1-8])G([01][0-9])).zip', filename)
    dir, curso, turno, grupo = m.groups()
    os.makedirs(f'/tmp/{dir}', exist_ok = True)
    os.system(f'cp {filename} /tmp/{dir}; cd /tmp/{dir}; unzip -o -q {filename}')
    args = '-std=gnu11 -Wall -Wextra -pedantic-errors -O'.split()
    files = glob.glob(f'/tmp/{dir}/*.c')
    res = subprocess.run(['gcc', *args, *files, '-lm'], stderr=subprocess.STDOUT, stdout=subprocess.PIPE, cwd = f'/tmp/{dir}')
    warnings = "NO"
    if(res.stdout):
        warnings = "YES!"
    print(f'Curso: {curso}\tTurno: {turno}\tGrupo: {grupo}\tWarnings: {warnings}\tFicheiros: {files}')

for filename in sys.argv[1:]:
    extrai(filename)
