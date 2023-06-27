# minishell

## Description

Project from 42 School
A simple re-creation of Bash in C and [Readline library](https://tiswww.case.edu/php/chet/readline/rltop.html)

## Installation

```
git clone git@github.com:Dot-kpp/minishell.git
make
```

## Goals

Draw a waiting prompt <br />
Have a dynamic history that can be used with arrow up and down <br />
Can execute any executable file relatively or via $PATH <br />
Process the single an double quotes <br />
Possess its own environement variables that can be called with $ <br />
Handle Redirections and Pipes <br />
Handle signals from ctrl-C ctrl-D and ctrl-/ according to Bash <br />
Have its own builtins commands : <br />
    **echo** with -n flag <br />
    **cd** only with 1 argument <br />
    **pwd** without flag <br />
    **export** without flag <br />
    **unset** without flag <br />
    **env** without flag nor argument <br />
    **exit** without flag <br />

## Usage

```
./minishell
```
Same usage as Bash
