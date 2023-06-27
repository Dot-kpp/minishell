# minishell

<p align="center">
  <img src="/screenshot.png" width="100%" />
</p>

## Description

Project from 42 School
A simple re-creation of Bash in C and [Readline library](https://tiswww.case.edu/php/chet/readline/rltop.html)

## Installation

```
git clone git@github.com:Dot-kpp/minishell.git
make
```

## Features

- Draw a waiting prompt
- Have a dynamic history that can be used with arrow up and down
- Can execute any executable file relatively or via $PATH
- Process the single an double quotes
- Possess its own environement variables that can be called with $
- Handle Redirections and Pipes
- Handle signals from ctrl-C ctrl-D and ctrl-/ according to Bash
- Have its own builtins commands :
    - **echo** with -n flag
    - **cd** only with 1 argument
    - **pwd** without flag
    - **export** without flag
    - **unset** without flag
    - **env** without flag nor argument
    - **exit** without flag

## Usage

```
./minishell
```
Same usage as Bash

## Credits

[fgeslin](https://github.com/KayzaFlo)
[jpilotte](https://github.com/Dot-kpp)
