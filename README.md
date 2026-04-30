*This project has been created as part of the 42 curriculum by vbleskin (vlad).*

# Minishell - As beautiful as a shell

## Description
Minishell is a project from the 42 School common core that involves creating a simplified shell. It is a recreation of a Unix shell (like Bash) that handles command execution, environment variables, pipes, redirections, and more.

The goal of this project is to understand the inner workings of a terminal, process management (`fork`, `execve`, `waitpid`), file descriptors manipulation (`pipe`, `dup2`), and signal handling.

### Features
- **Command Execution**: Search and launch executables based on the `PATH` or relative/absolute paths.
- **Built-ins**: Implemented `echo` (with `-n`), `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.
- **Pipes (`|`)**: The output of each command in a pipeline is connected to the input of the next.
- **Redirections**:
    - `<`: Redirect input.
    - `>`: Redirect output (truncate).
    - `>>`: Redirect output (append).
    - `<<`: Heredoc support.
- **Environment Variables**: Expansion of `$VAR` and `$?` (exit status).
- **Signal Handling**: Correct behavior for `Ctrl-C`, `Ctrl-D`, and `Ctrl-\` in interactive and execution modes.
- **Bonus Part**:
    - Logical operators `&&` and `||` with correct priority.
    - Subshells using parentheses `( )`.
    - Wildcards `*` for the current directory.

## Instructions

### Compilation
The project uses a `Makefile` for compilation. Ensure you have `libreadline-dev` installed on your system.

```bash
make
```

### Usage
Run the generated binary:

```bash
./minishell
```

You can then type commands as you would in a regular shell.

## Resources
- **GNU Readline Documentation**: For handling user input and history.
- **Linux Manual Pages**: `man 2 fork`, `man 2 pipe`, `man 2 execve`, `man 2 sigaction`.
- **Bash Reference Manual**: To understand the expected behavior of a POSIX shell.
- **AI Usage**: Gemini CLI was used as a peer-programming assistant to:
    - Scaffold the execution engine (pipes, redirections, logical operators).
    - Debug memory issues (identifying double frees in AST nodes).
    - Implement the hash map utility functions for environment management.
    - Assist in installing system dependencies (`libreadline-dev`).
