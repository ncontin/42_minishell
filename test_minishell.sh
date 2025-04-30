#!/bin/bash

ulimit -v 105000
ulimit -n 64
ulimit -t 1

valgrind \
	--leak-check=full \
	--show-leak-kinds=all \
	--track-fds=yes \
	--suppressions=vsupp \
	--error-exitcode=42 \
	./minishell << EOF
	echo "test here_doc"
	line 1
	line 2
	EOF2
	ls -l
	exit
	EOF
	echo 42 | echo no | echo smth | grep 42
	/bin/env | grep "_="
	echo test | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e | cat -e
	|ls | ls
