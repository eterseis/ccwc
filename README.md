# ccwc
Print newline, word, and byte counts.

## Synopsis

ccwc [OPTION]... [FILE]

If no file is specified, read standard input.
If no option provided, `ccwc` will print the newline, word, and byte counts.
Written in C.

## How To Use
To clone and run this application, you'll need [Git](https://git-scm.com) and GCC.
#### From your command line:
```bash

# Clone this repository
$ git clone git@github.com:eterseis/ccwc.git

# Go into the repository
$ cd ccwc

# Compile with gcc
$ gcc ccwc.c -o ccwc

# Run the app
% ./ccwc [OPTION]... [FILE]
```

## Options
- `-c` print the byte counts
- `-m` print the character counts
- `-l` print the newline counts
- `-w` print the word counts

## Examples

    $ ./ccwc -c README.md
    ->  993 README.md

    $ cat README.md | ./ccwc
    ->  765     37      136
> Output Order -> newlines words bytes characters [filename]

## Credits
[CodingChallenges](https://www.codingchallenges.fyi)
