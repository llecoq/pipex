<p align="center">
  <a href="https://42lyon.fr/">
    <img src="./assets/final_grade.png" alt="pipex" width=200 height=170>
  </a>

  <h2 align="center">pipex</h2>

  <p align="center">
    This project will let you discover in detail a UNIX mechanism that you already know
    by using it in your program.
    <br>
    <br>
    /!\ SUBJECT LINKED IS DIFFERENT THAN THE ONE USED FOR THIS PROGRAM /!\
    <br>
    <a href="https://github.com/llecoq/pipex/blob/master/assets/en.subject.pdf">English Subject </a>
    |
    <a href="https://github.com/llecoq/pipex/blob/master/assets/fr.subject.pdf"> Sujet en Francais</a>
  </p>
</p>


## Table of contents

- [Quick start](#quick-start)
- [What's included](#whats-included)
- [Creators](#creators)


## Quick start

Pipex with full bonus

usage :
```
./pipex file1 cmd1 cmd2 cmd3 ... cmdn file2
```

## What's included

```
pipex
├── Makefile
├── assets
│   ├── en.subject.pdf
│   ├── final grade.png
│   └── fr.subject.pdf
├── includes
│   ├── enum.h
│   └── pipex.h
├── libft with gnl
│
└── srcs
    ├── executor
    │   ├── create_redirection.c
    │   ├── dup_redirections.c
    │   └── executor.c
    ├── executor_utils
    │   ├── build_file_path.c
    │   ├── create_argv.c
    │   ├── create_pipe.c
    │   ├── exit_status.c
    │   └── path_is_unset.c
    ├── main.c
    ├── parsing
    │   ├── heredoc.c
    │   ├── parser.c
    │   ├── store_cmds.c
    │   └── store_path.c
    ├── tokenizer
    │   ├── store_token_list.c
    │   ├── store_tokens.c
    │   └── tokenizer.c
    └── utils
        ├── calloc_pipex.c
        ├── clear_memory.c
        ├── del.c
        ├── error.c
        └── print_list.c
```

## Creators

**llecoq**

- <https://github.com/llecoq>
