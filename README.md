# minishell
As beautiful as a shell.

**Build:**
```
 make
```

**Usage:**
```
./minishell
```

**Builtins:**
 - cd
 - pwd
 - env
 - setenv
 - unsetenv
 - echo
 - exit

**Bonuses:**
 - Acces rights check for commands
 - Change SIGINT dispositon
 - Command separator control-operator (;)
 - Prompt shows current working directory
 - Builtin echo option -n
 - Builtin env can execute
 - Builtin env option -0: shows env without newlines
 - Builtin env option -i: execute with an empty environment
 - Builtin setenv shows env if no arguments are passed
 - Builtin exit can take a status number as argument
 - Builtin pwd
 - PWD and OLDPWD are set when changing dir
 - SHELL is set appropriately
 - SHLVL incrementation
 - Piping to minishell available
 - Check for directory before execution
