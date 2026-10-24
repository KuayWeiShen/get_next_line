*This project has been created as part of the 42 curriculum by wkuay*

# get_next_line - Milestone 1

A 42 School project that implements a C function to read line-by-line from a file descriptor (`fd`), managing persistent memory state across calls and preventing memory leaks under all circumstances.

---

## Overview

The goal of `get_next_line` is to code a function that returns a line read from a file descriptor. Repeated calls to `get_next_line()` allow you to read the entire text file pointed to by the file descriptor, one line at a time, until the End-Of-File (EOF) or an error occurs.

---

## Features & Implementation Details

- **Static Variable Buffer (`saved_str`)**: Uses a static pointer to store leftover characters across function calls when reading chunks larger or smaller than a single line.
- **Error Handling**: Properly cleans up memory on read errors (`-1`), EOF (`0`), or unexpected `malloc` failures.
- **Memory Safety**: Includes a `free_str` helper function to handle string pointer dereferencing and nullification, preventing dangling pointers or double frees.
- **Multiple File Descriptors**: Supports reading from multiple file descriptors concurrently without losing the reading state or leaking memory.
- **Array vs Linked List**: Two different approaches for reference and understanding.

---

## File Structure

| File | Description |
| :--- | :--- |
| `get_next_line.c` / `_bonus.c` | Core logic containing `get_next_line`, `read_and_store`, `line_separator`, `free_str`, `ft_substr`. and `remove_file_node`. |
| `get_next_line_utils.c` | Helper functions (`ft_strlen`, `ft_memcpy`, `ft_strchr`, `ft_strdup`, `ft_strjoin` and `gnl_new_node`). |
| `get_next_line.h` | Header file containing prototypes, required libraries (`unistd.h`, `stdlib.h`, `stddef.h`), the fallback `BUFFER_SIZE` macro and `t_gnl` structure definition. |

---

## Getting Started

### 1. Function Prototype

```c
char *get_next_line(int fd);
```

- **Parameters**: `fd` — File descriptor to read from.
- **Return Value**: 
  - Read line (including `\n` if present).
  - `NULL` if there is nothing else to read or if an error occurred.

---

### 2. Compilation

Compile `get_next_line` along with your main program. You can customize the buffer size at compile time using the `-D BUFFER_SIZE=n` flag:

```bash
# Mandatory compilation
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl_test
# Bonus compilation (Multi-FD support)
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o gnl_bonus
```

---

### 3. Example Code (`main.c`)

```c
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line_bonus.h"

int main(void)
{
    char    *line;
    int     line_num;

    printf("Enter text (Ctrl+D to exit):\n");
    line_num = 1;
    
    // fd 0 represents standard input (stdin)
    while ((line = get_next_line(0)) != NULL)
    {
        printf("[Stdin Line %d]: %s", line_num++, line);
        free(line);
    }
    printf("\nEnd of input reached.\n");
    return (0);
}
```
```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
    int     fd;
    char    *line;
    int     line_num;

    if (argc < 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return (1);
    }
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return (1);
    }
    line_num = 1;
    while (line = get_next_line(fd) != NULL)
    {
        printf("[%d]: %s", line_num++, line);
        free(line);
    }
    close(fd);
    return (0);
}
```
```c
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "get_next_line_bonus.h"

int main(int argc, char **argv)
{
    int     fd1;
    int     fd2;
    char    *line1;
    char    *line2;

    if (argc < 3)
    {
        printf("Usage: %s <file1> <file2>\n", argv[0]);
        return (1);
    }

    fd1 = open(argv[1], O_RDONLY);
    fd2 = open(argv[2], O_RDONLY);

    if (fd1 < 0 || fd2 < 0)
    {
        perror("Error opening files");
        return (1);
    }

    printf("--- Interleaving reads from FD %d and FD %d ---\n", fd1, fd2);

    // Read alternately from fd1 and fd2 to prove independent state tracking
    line1 = get_next_line(fd1);
    line2 = get_next_line(fd2);

    if (line1)
    {
        printf("[FD %d]: %s", fd1, line1);
        free(line1);
    }
    if (line2)
    {
        printf("[FD %d]: %s", fd2, line2);
        free(line2);
    }

    // Read another line from fd1 first, then fd2
    line1 = get_next_line(fd1);
    if (line1)
    {
        printf("[FD %d]: %s", fd1, line1);
        free(line1);
    }

    line2 = get_next_line(fd2);
    if (line2)
    {
        printf("[FD %d]: %s", fd2, line2);
        free(line2);
    }

    close(fd1);
    close(fd2);
    return (0);
}
```
---

## AI Usage Disclosure

In accordance with 42 School guidelines, AI tools were utilised during this project for the following specific tasks

1. Debugging: Troubleshooting syntax errors, tab space indentation issues (missing separator).
2. Memory Leak Analysis: Identifying memory leaks in the helper functions and code.
3. Code Review & Formatting Checks: Validating Norminette compliance regarding function line limits (under 25 lines) and variable declaration scopes.
4. Documentation: AI was used to help structure and draft this `README.md` to ensure all required project specifications and algorithm details were met.
