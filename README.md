# 🐚 Minishell

> A mini Unix shell implemented in C that replicates basic behavior of bash, including parsing, execution, redirections, pipes, and environment management.

## 📘 Project Description

**Minishell** is one of the most complex projects at 42. The goal is to recreate a functional command-line shell that interprets and executes user commands, mimicking many features of Bash.

This project involves implementing:
- A lexer & parser
- Environment variable management
- Command execution with pipes & redirections
- Signal handling
- Built-in commands (like `cd`, `echo`, `export`, `unset`, etc.)

## 🛠️ Skills Learned

- Lexical analysis and syntax parsing
- Process and file descriptor management
- System call usage: `fork`, `execve`, `pipe`, `dup2`, `wait`, etc.
- Signal handling (`SIGINT`, `SIGQUIT`, etc.)
- Job control (basic)
- Memory management and error handling
- Modular C architecture and linked lists

## 🚀 Getting Started

### ✅ Compilation

```bash
make
./minishell
