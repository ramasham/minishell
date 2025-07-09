# 🐚 Minishell

<p align="center">
  <img src="https://img.shields.io/badge/42-Project-blue?style=flat&logo=42&logoColor=white" />
  <img src="https://img.shields.io/badge/C-language-blue?style=flat&logo=c&logoColor=white" />
</p>

**Minishell** is a simplified Unix shell implemented in C as part of the [42 School](https://42.fr/) curriculum.  
It replicates many core functionalities of Bash, including command parsing, piping, redirections, environment variables, and built-in commands — all done from scratch with strict constraints (no external parsing libraries, no `system()` calls).

> 🧠 **Goal:** Understand how shells work internally, manage processes, signals, I/O, and build a fully functional terminal interface.

---

## 🚀 Features

- 🧾 **Lexical Analysis & Parsing**
  - Tokenizes input while handling quotes and escapes
  - Builds a parse tree or linked command structure for execution

- 🔁 **Built-in Commands**
  - `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
  - Behaves as close as possible to Bash

- 📤 **Redirections**
  - Input `<`, Output `>`, Append `>>`
  - Heredocs (`<<`) with proper signal handling

- 🔗 **Pipes**
  - Supports multiple pipes: `ls | grep .c | wc -l`

- 🌍 **Environment Variable Expansion**
  - Expands `$VAR` and special `$?`
  - Keeps internal copy of environment (`envp`)

- 🧵 **Process Management**
  - Executes external programs with `fork`, `execve`, and `waitpid`
  - Isolates builtins (in parent vs child process when needed)

- 🚨 **Signal Handling**
  - Custom handling of `SIGINT`, `SIGQUIT`, heredoc interrupt
  - Matches Bash behavior (e.g., Ctrl+C doesn't quit the shell)

- 🔎 **Error Messages**
  - Detects syntax errors (`unexpected token '|'`)
  - Handles edge cases like open quotes or invalid identifiers

---
```
## 📂 Project Structure
minishell/
├── src/
│ ├── lexer/ # Tokenizer logic
│ ├── parser/ # Command structure builder
│ ├── executor/ # Builtins, piping, redirection
│ ├── signals/ # Signal handling
│ └── utils/ # String, memory, and helper tools
├── include/
│ └── minishell.h
├── libft/ # Custom standard library functions
├── Makefile
└── README.md
```
