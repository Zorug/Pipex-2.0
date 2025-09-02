Pipex

📖 Sobre o projeto

O Pipex é um projeto da 42 que tem como objetivo recriar em C o
comportamento de redirecionamento de pipes do shell Unix.
Ele permite compreender em profundidade como funciona a comunicação
entre processos utilizando fork, pipe, dup2, e execve.

O programa deve reproduzir o seguinte comportamento do shell:

    $ < file1 cmd1 | cmd2 > file2

------------------------------------------------------------------------

🚀 Execução

Uso

    ./pipex file1 cmd1 cmd2 file2

-   file1 → arquivo de entrada
-   cmd1 → primeiro comando a ser executado
-   cmd2 → segundo comando a ser executado
-   file2 → arquivo de saída

Exemplos

    $ ./pipex infile "ls -l" "wc -l" outfile
    # Equivalente a: < infile ls -l | wc -l > outfile

    $ ./pipex infile "grep a1" "wc -w" outfile
    # Equivalente a: < infile grep a1 | wc -w > outfile

------------------------------------------------------------------------

📦 Compilação

O projeto é compilado com um Makefile, que inclui as regras:

-   make ou make all → compila o projeto
-   make clean → remove arquivos objeto
-   make fclean → remove arquivos objeto e binário
-   make re → recompila o projeto do zero
-   make bonus → compila a versão bônus (se implementada)

Flags utilizadas: -Wall -Wextra -Werror

------------------------------------------------------------------------

🔧 Funções autorizadas

-   open, close, read, write
-   malloc, free, perror, strerror, access
-   dup, dup2, execve, exit, fork, pipe, unlink
-   wait, waitpid
-   ft_printf (ou equivalente implementado)

Biblioteca libft autorizada.

------------------------------------------------------------------------

✅ Requisitos

-   O projeto deve estar de acordo com a Norm da 42.
-   Nenhum erro inesperado (segfault, bus error, etc).
-   Nenhum memory leak será tolerado.
-   O comportamento deve ser idêntico ao do shell.

------------------------------------------------------------------------

⭐ Bônus

-   Suporte a múltiplos pipes:

        ./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
        # Equivalente a: < file1 cmd1 | cmd2 | cmd3 ... | cmdn > file2

-   Suporte a here_doc:

        ./pipex here_doc LIMITER cmd1 cmd2 file
        # Equivalente a: cmd << LIMITER | cmd1 >> file

  ⚠️ O bônus só será avaliado se a parte obrigatória estiver 100%
  funcional.

------------------------------------------------------------------------

📂 Estrutura esperada

    .
    ├── Makefile
    ├── pipex.c
    ├── pipex.h
    ├── utils.c
    ├── ...
    └── libft/   (se utilizada)

------------------------------------------------------------------------

👨‍💻 Autor

Projeto realizado como parte do currículo da 42.
