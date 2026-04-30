# Identified Bugs and Logic Flaws

This document outlines the critical bugs, logic flaws, and missing features identified in the current state of the Minishell project.

## 1. Critical Execution Issues

### 1.1 Unimplemented Execution Engine
*   **Undefined Symbols**: The function `ft_exec_command` is called in `src/exec/exec.c` but does not exist in the codebase.
*   **Missing System Calls**: There are no calls to `fork()`, `execve()`, `pipe()`, or `dup2()`. The shell cannot currently execute external commands or handle inter-process communication.
*   **Node Handling**: `ft_exec_node` only handles `NODE_COMMAND`. Logic for `NODE_PIPE`, `NODE_AND`, `NODE_OR`, and all redirection nodes is missing.

### 1.2 Build System Failure
*   **Makefile Paths**: The `Makefile` points to a non-existent `src/builtin` directory instead of `src/exec/built-in`. Consequently, none of the built-in commands (`cd`, `echo`, `exit`, etc.) are included in the compilation.

NOTE : CHECK SI LES NODES DE L'AST SONT NULL AU DEBUT DE L'EXEC (selon le type check pour redir_data et cmd_data aussi)

---

<!-- ## 2. Parsing & AST Logic Flaws -->

<!-- ### 2.1 Operator Precedence
*   **Left-to-Right Bias**: `ft_find_operator` in `src/parsing/ast/tree.c` returns the first operator it encounters. This results in incorrect associativity for logical operators.
    *   *Example*: `cmd1 && cmd2 || cmd3` is parsed as `cmd1 && (cmd2 || cmd3)` instead of `(cmd1 && cmd2) || cmd3`.
*   **Nesting Awareness**: The operator search logic does not account for parentheses. It will incorrectly pick an operator inside a subshell as the root of the tree if it appears first in the token stream. -->

<!-- ### 2.2 Syntax Validation
*   **Empty Nodes**: The current syntax check allows for some edge cases that might result in `NULL` nodes being passed to logic that expects valid command data. -->

<!-- --- -->

<!-- ## 3. Environment & Hash Table Issues

### 3.1 Duplicate Keys
*   **Insertion Logic**: `ft_fill_item` in `src/parsing/expand/hash.c` appends new items to the end of a chain without checking if the key already exists.
    *   *Result*: Updating an environment variable creates a duplicate entry. Lookups will likely return the oldest (stale) value rather than the updated one.

--- -->

## 4. Expansion & Wildcard Flaws

### 4.1 Quoted Wildcard Expansion
*   **Incorrect Ordering**: `ft_expand_single_arg_wildcard` calls `ft_remove_quotes` before checking for the wildcard.
    *   *Result*: `ls "*"` will expand to all files in the directory because the quotes are stripped before the shell checks if the `*` was literal or special.

### 4.2 Ambiguous Redirects
*   **Expansion Edge Cases**: While `ft_check_ambiguous_redirect` exists, the integration in `ft_expand_redir_node` does not fully handle cases where a variable expansion results in an empty string or multiple words if it wasn't quoted in the original command.

---

## 5. Memory & Signal Management

### 5.1 Heredoc Cleanup
*   **FD Leaks**: There is no clear mechanism in the current code to ensure that temporary files or pipes used for heredocs are closed and unlinked in all exit paths (especially after a SIGINT).


Built in export fonctionne pas

Wildcards dans les heredocs fonctionne pas

Make re fonctionne pas
