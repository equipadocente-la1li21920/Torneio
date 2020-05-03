import sys, os, re, subprocess, glob, os.path

def check_for_warnings(folder):
    if not os.path.isdir(folder):
        return False
    args = '-std=gnu11 -Wall -Wextra -pedantic-errors -O'.split()
    files = glob.glob(f'{folder}/*.c')
    res = subprocess.run(['gcc', *args, *files, '-lm'], stderr=subprocess.STDOUT, stdout=subprocess.PIPE, cwd = folder)
    warnings = True
    if(res.stdout):
        warnings = False
    return warnings

def count_XML_files(folder):
    files = glob.glob(f'{folder}/*.xml')
    tam = len(files)
    return tam if tam > 0 else "NO!"

def count_C_files(folder):
    files = glob.glob(f'{folder}/*.[hc]')
    return len(files)

def check_for_readme(folder):
    possibilities = 'README Readme readme'.split()
    return any(os.path.isfile(f'{folder}/{poss}.md') for poss in possibilities)


def extrai(filename):
    m = re.match(r'((li2|la1)PL([1-8])G([01][0-9])).zip', filename)
    if not m:
        print(f'O nome do ficheiro {filename} não está correto')
        return
    dir, curso, turno, grupo = m.groups()
    base_dir = f'/tmp/{dir}'
    code_dir = f'/tmp/{dir}/projeto'
    doc_dir = f'/tmp/{dir}/doc'
    bot_dir = f'/tmp/{dir}/bot'
    os.makedirs(base_dir, exist_ok = True)
    os.system(f'cp {filename} {base_dir}; cd {base_dir}; unzip -o -q {filename}')

    warnings = 'NO' if any(check_for_warnings(folder) for folder in [code_dir, bot_dir]) else 'YES!'
    num_files_projeto = count_C_files(code_dir) if os.path.isdir(code_dir) else "NO!"
    num_files_bot = count_C_files(bot_dir) if os.path.isdir(bot_dir) else "NO!"

    print(f'Curso: {curso}\tTurno: {turno}\tGrupo: {grupo}\tREADME: {check_for_readme(base_dir)}\t#Doc: {count_XML_files(doc_dir)}\tWarnings: {warnings}\t#files_projeto: {num_files_projeto}\t#files_bot: {num_files_bot}')

for filename in sys.argv[1:]:
    extrai(filename)
