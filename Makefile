##
## EPITECH PROJECT, 2020
## PSU_minishell1_2019
## File description:
## Makefile
##

SRC = src/shell.c \
	src/prompt.c \
	src/execute.c \
	src/alias.c \
	src/redirections/redirection_manager.c \
	src/redirections/redirections.c \
	src/redirections/redirections_functions.c \
	src/redirections/redirection_validator.c \
	src/env.c \
	src/args.c \
	src/builtin/builtin_history.c \
	src/builtin/builtin_history_two.c \
	src/builtin/builtin_manager.c \
	src/builtin/builtin_env.c \
	src/builtin/builtin_source.c \
	src/builtin/builtin_source_two.c \
	src/builtin/builtin_which.c \
	src/builtin/builtin_where.c \
	src/builtin/builtin_alias.c \
	src/builtin/builtin_unalias.c \
	src/builtin/builtin_echo.c \
	src/builtin/builtin_if.c \
	src/builtin/builtin_if_two.c \
	src/signal.c \
	src/free_env.c \
	src/utility/same_var.c \
	src/utility/tostr.c \
	src/utility/envvar_is_valid.c \
	src/utility/to_array.c \
	src/utility/catpath.c \
	src/utility/split_str.c \
	src/utility/envpath.c \
	src/utility/fusion.c	\
	src/utility/split_commands.c \
	src/utility/get_return.c \
	src/parser/parser.c \
	src/parser/quotes.c \
	src/parser/double_quotes.c \
	src/parser/parser_utilities.c \
	src/parser/parser_vars_utilities.c \
	src/utility/eof.c \
	src/key_bindings/basic_typing_functions.c \
	src/key_bindings/default_bindings.c \
	src/key_bindings/control_commands.c \
	src/key_bindings/move_commands.c \
	src/my_ncurses/my_ncurses.c \
	src/my_ncurses/string_utils.c \
	src/my_ncurses/pause_utils.c \
	src/key_bindings/autocompletion.c \
	src/builtin/builtin_bindkey.c \
	src/key_bindings/other_bindings.c \
	src/builtin/builtin_vars.c \
	src/key_bindings/signals.c \
	src/prompt/prompt_values.c \
	src/prompt/prompt_utilities.c

OBJ = $(SRC:%.c=%.o)
OBJ += src/main.o

TESTS = tests/tenv.c \
	tests/targc.c \
	tests/texecute.c \
	tests/tcd.c \
	tests/tsource.c \
	tests/techo.c

COVERAGE = -lcriterion --coverage

UT = ./unit_tests

NAME = 42sh

CC = gcc

INCLUDE = -I ./include

CFLAGS = $(INCLUDE) -Wall -Wextra -Wshadow -Wno-unused-parameter

LDFLAGS = -lncurses

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

tests_run: clean
	$(CC) -o $(UT) $(TESTS) $(SRC) $(COVERAGE) -g $(CFLAGS) $(LDFLAGS)
	$(UT)

func: all
	cd tests/tester/ && cp ../../$(NAME) $(NAME) && ./tester.sh
	rm tests/tester/$(NAME)

clean:
	$(RM) $(OBJ)
	$(RM) *.gc*

fclean: clean
	$(RM) $(NAME)
	$(RM) $(UT)

re: fclean all

dbg: CFLAGS += -g
dbg: re