# Minishell

Minishell is a simple Unix shell implementation written in C as part of the 42 School curriculum. The project recreates basic Bash behavior, including command execution, pipes, redirections, environment variables, and built-in commands.

## Features

* Execute commands and programs
* Pipes and redirections
* Environment variable expansion
* Built-in commands (`cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`)
* Signal handling
* Command history with Readline

## Compilation

```bash
make
```

## Run

```bash
./minishell
```

## My Contribution

* Implemented command execution logic
* Designed and implemented environment variable handling from scratch in C
* Combined linked list and map-like data structures for efficient environment management
* Worked on pipe handling and multi-process execution flow
* Implemented inter-process communication using pipes and file descriptors

## Example

```bash
minishell$ echo Hello
minishell$ ls -la | grep minishell
minishell$ cat < infile > outfile
```
