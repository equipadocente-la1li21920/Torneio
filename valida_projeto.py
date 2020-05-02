import sys, os, re, subprocess, glob, os.path

def check_for_warnings(folder):
    args = '-std=gnu11 -Wall -Wextra -pedantic-errors -O'.split()
    files = glob.glob(f'{folder}/*.c')
    res = subprocess.run(['gcc', *args, *files, '-lm'], stderr=subprocess.STDOUT, stdout=subprocess.PIPE, cwd = folder)
    warnings = True
    if(res.stdout):
        warnings = False
    return warnings

def count_XML_files(folder):
    files = glob.glob(f'{folder}/*.xml')
    return len(files)

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
    os.makedirs(f'/tmp/{dir}', exist_ok = True)
    code_dir = f'/tmp/{dir}/projeto'
    doc_dir = f'/tmp/{dir}/doc'
    bot_dir = f'/tmp/{dir}/bot'
    os.system(f'cp {filename} /tmp/{dir}; cd /tmp/{dir}; unzip -o -q {filename}')

    warnings = 'NO' if any(check_for_warnings(folder) for folder in [code_dir, bot_dir]) else 'YES!'

    print(f'Curso: {curso}\tTurno: {turno}\tGrupo: {grupo}\tREADME: {check_for_readme(dir)}\t#Doc: {count_XML_files(doc_dir)}\tWarnings: {warnings}\t#files_projeto: {count_C_files(code_dir)}\t#files_bot: {count_C_files(bot_dir)}')

for filename in sys.argv[1:]:
    extrai(filename)
