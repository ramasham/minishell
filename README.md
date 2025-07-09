# 🐚 Minishell

<p align="center">
  <img src="https://img.shields.io/badge/42-Project-blue?style=flat&logo=42&logoColor=white" />
  <img src="https://img.shields.io/badge/C-language-blue?style=flat&logo=c&logoColor=white" />
</p>


**Minishell** is a fully functional minimal Unix shell implemented in C as part of the [42 School](https://42.fr/) curriculum.  
It replicates core features of the Bash shell with strict project constraints, providing a deep dive into shell internals and systems programming fundamentals.

> 🧠 **Objective:**  
> To understand how command-line interpreters work at a low level — from lexical analysis and parsing to process management, I/O redirection, and signal handling — by building a working shell from the ground up without relying on external libraries or system helpers like `system()`.

---

## 🔍 Background: How Unix Shells Work

Unix shells like **Bash** serve as the command-line interface between users and the operating system kernel. They are responsible for:

- **Command Parsing:** Interpreting raw input strings, recognizing commands, arguments, pipes, and redirections.
- **Process Control:** Creating child processes using `fork()`, running commands via `execve()`, and synchronizing with `waitpid()`.
- **I/O Management:** Redirecting input/output streams using file descriptors (`dup2()`), enabling pipelines, and handling heredocs.
- **Environment Management:** Maintaining environment variables that influence command behavior and system operations.
- **Signal Handling:** Responding to user interrupts (`Ctrl+C`), quit signals (`Ctrl+\`), and gracefully managing job control.
- **Built-in Commands:** Implementing shell internal commands that alter shell state without launching external programs.

This project explores all these layers, giving insight into how a shell interprets and executes commands exactly as Bash does, but with the complexity scaled down to a manageable learning project.

---

## 📂 Project Structure
```
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

## 🚀 Key Features & Technical Highlights

- **Robust Lexical Analyzer:**  
  Handles complex tokenization respecting quoting rules (single/double quotes), escape sequences, and token delimiters.

- **Context-Aware Parser:**  
  Builds an abstract syntax tree or linked list of commands, distinguishing between built-ins, external commands, and operators (`|`, `<`, `>`, `>>`, `<<`).

- **Built-in Commands Modeled on Bash:**  
  Implements internal commands with precise behaviors and edge case handling (`export` with/without values, `unset`, `exit`, etc.).

- **Advanced Redirection Support:**  
  Supports input/output redirection including heredocs (`<<`), with signal-safe interruption and cleanup.

- **Full Pipeline Support:**  
  Enables chaining of multiple commands via pipes, correctly managing file descriptors and process synchronization.

- **Environment Variable Expansion:**  
  Expands variables like `$HOME`, `$?`, including inside quotes as Bash does, maintaining a private copy of the environment.

- **Process Lifecycle Management:**  
  Uses `fork()`, `execve()`, and `waitpid()` to spawn and control command execution, isolating built-ins and external binaries properly.

- **Signal Handling that Mimics Bash:**  
  Custom handlers for `SIGINT`, `SIGQUIT`, and others allow expected terminal behaviors (e.g., Ctrl+C cancels current command but keeps shell running).

- **Error Detection & Reporting:**  
  Provides clear, Bash-like error messages on syntax errors, missing commands, invalid identifiers, or unexpected tokens.

---

## ⌨️ Supported Built-ins

| Command  | Description                            |
|----------|-------------------------------------|
| `echo`   | Prints text to standard output      |
| `cd`     | Changes current working directory   |
| `pwd`    | Prints current working directory    |
| `export` | Sets environment variables          |
| `unset`  | Removes environment variables       |
| `env`    | Displays current environment        |
| `exit`   | Exits the shell with a status code  |

---

\## 🙏 Final Notes

Thank you for exploring this project!  
Minishell was a challenging yet rewarding journey into the heart of Unix shells and systems programming.

## 👥 Team
This project was developed as part of the 42 School curriculum by:  
🧑‍💻 [@ramasham](https://github.com/ramasham)  
🧑‍💻 [@sarahayman22](https://github.com/lujaburomman)  
