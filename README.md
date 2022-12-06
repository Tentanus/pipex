# Pipex
### A 42 (Codam) Project

[![CodeFactor](https://www.codefactor.io/repository/github/tentanus/pipex/badge)](https://www.codefactor.io/repository/github/tentanus/pipex)

*This project will let you discover in detail a UNIX mechanism that you already know
by using it in your program.*

This project means to recreate the pipe function. This is done using UNIX systemcalls (e.g. fork, pipe and execve).

##: Usage

The progam can be compiled using the Makefile included in the repo:

```bash
> make pipex
```

Pipex should behave the same as a pipe `|` in BASH

```bash
./pipex file1 cmd1 cmd2 file2
```

```bash
cmd1 < file1 | cmd2 > file2
```

