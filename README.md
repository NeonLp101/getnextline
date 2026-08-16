*This project has been created as part of the 42 curriculum by lernst.*

# get_next_line

## Description
A C function that reads a text file (or stdin) one line at a time,
no matter the buffer size. Each call to `get_next_line(fd)` returns
the next line including its terminating `\n` (except at EOF without
newline). Returns NULL on EOF or error.

## Instructions
Compile together with your own files:

    cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c

`BUFFER_SIZE` is optional; a default of 42 is defined in the header.

## Algorithm
A static stash string persists between calls and accumulates raw
read() output. Each call reads BUFFER_SIZE bytes at a time only until
the stash contains a newline (or EOF), so the function never reads
more of the file than necessary. The line up to and including the
newline is extracted and returned; the remainder stays in the stash
for the next call. This was chosen over fixed-size line buffers
because lines can be arbitrarily long, and over reading the whole
file because the subject forbids it and it would waste memory on
large files or never terminate on stdin/pipes. All error paths free
the stash and reset the static pointer so subsequent calls stay safe.

## Resources
- man 2 read, man 3 malloc
- Static variables in C: https://en.cppreference.com/w/c/language/storage_duration
- File descriptors: https://en.wikipedia.org/wiki/File_descriptor

AI usage: AI (Claude) was used to discuss the stash-based approach,
review edge cases (BUFFER_SIZE=1, files without trailing newline,
read errors) and memory-leak handling. All code was reviewed,
tested and understood by the author.