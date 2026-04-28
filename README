# Minishell

This Ecole 42 project is a custom implementation of a command-line interpreter, similar to shells like `bash` or `zsh`. The primary goal is to replicate core shell functionalities, providing a deeper understanding of process management, command parsing, and execution flows within a Unix-like environment. The shell processes user input, handles command execution, manages environment variables, and supports essential features like pipes and redirections.

## Features

-   **Command Parsing and Execution:** Parses command lines with arguments, quotes (`'` and `"`), and executes external commands found in the system's `PATH`.
-   **Pipelines:** Supports command pipelines using the `|` operator to chain multiple commands.
-   **I/O Redirections:**
    -   `<`: Redirect standard input.
    -   `>`: Redirect standard output (truncate).
    -   `>>`: Redirect standard output (append).
-   **Here Documents:** Implements here-documents (`<<`) for providing multi-line input to commands.
-   **Environment Variable Expansion:**
    -   Expands environment variables (e.g., `$USER`, `$PATH`).
    -   Supports special variables: `$?` (last command's exit status), `$$` (process ID), and `$UID`.
-   **Signal Handling:**
    -   `Ctrl+C` (`SIGINT`): Displays a new prompt without exiting the shell, or terminates the running process.
    -   `Ctrl+\\` (`SIGQUIT`): Ignored in the interactive prompt; terminates the running process with a core dump.
    -   `Ctrl+D`: Exits the shell.
-   **Built-in Commands:**
    -   `echo`: Prints arguments to the standard output, with support for the `-n` flag.
    -   `cd`: Changes the current directory.
    -   `pwd`: Displays the current working directory.
    -   `export`: Sets or displays environment variables.
    -   `unset`: Removes environment variables.
    -   `env`: Lists all environment variables.
    -   `exit`: Terminates the shell with a specified exit status.

## Getting Started

### Prerequisites

-   A Unix-like operating system (Linux, macOS)
-   `gcc` compiler
-   `make`
-   `readline` library

### Installation & Execution

1.  **Clone the repository:**
    ```sh
    git clone https://github.com/kalirina/minishell.git
    cd minishell
    ```

2.  **Compile the project:**
    ```sh
    make
    ```

3.  **Run the shell:**
    ```sh
    ./minishell
    ```

## Makefile Commands

This project includes a `Makefile` with several useful targets:

-   `make` or `make all`: Compiles the source files and creates the `minishell` executable.
-   `make clean`: Removes all intermediate object files.
-   `make fclean`: Removes all compiled files, including the `minishell` executable.
-   `make re`: Cleans the project and recompiles everything from scratch.
-   `make valgrind`: Runs `minishell` with Valgrind to check for memory leaks. A suppression file (`ignore.supp`) is used to filter out known leaks from the `readline` library.
