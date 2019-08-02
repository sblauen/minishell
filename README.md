# minishell
A basic shell implementation.

## Table of Content
* [minishell](#minishell)
* [Table of Content](#table-of-content)
* [Synopsis](#synopsis)
* [Description](#description)
* [Build](#build)
* [Usage](#usage)

## Synopsis
[Minishell][1] is the second project of [42][2]'s Unix branch curriculum. The aim is to discover how a shell basically works (processes and execution).  

## Description

**Builtins:**
 - `cd [-] | [DIR]`,
 - `pwd`,
 - `echo [-n] [STRING]...`,
 - `env [-0] | [-i] [COMMAND [ARG]...]`,
 - `setenv [NAME] [VALUE]`,
 - `unsetenv NAME`,
 - `exit [STATUS]`.

**Bonuses:**
 - Acces rights check for commands,
 - Change SIGINT dispositon,
 - Command separator control-operator (`;`),
 - Prompt shows current working directory,
 - Builtin `echo` `-n` option,
 - Builtin `env` can execute,
 - Builtin `env` `-0` option: shows env without newlines,
 - Builtin `env` `-i` option: execute with an empty environment,
 - Builtin `setenv` behaves like env if no arguments are passed,
 - Builtin `exit` can take a status number as argument,
 - Builtin `pwd`,
 - PWD and OLDPWD are set when changing dir,
 - SHELL is set appropriately,
 - SHLVL incrementation,
 - Pipe to minishell possible,
 - Check for directory before execution.

The input is canonical, there is no command-line edition.

## Build
```
$ git clone https://github.com/sblauen/minishell.git && cd minishell && make
```

## Usage
```
./minishell
```

[1]: https://cdn.intra.42.fr/pdf/pdf/1409/minishell.en.pdf "minishell"
[2]: https://42.fr "42Born2Code"
