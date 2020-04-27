##
## EPITECH PROJECT, 2019
## libmy
## File description:
## makefile libmy
##

NAME = libmy.a

SRC 	= 	sources/my_compute_power_rec.c	\
		sources/my_compute_square_root.c \
		sources/my_find_prime_sup.c \
		sources/my_getnbr.c \
		sources/my_getnbr_base.c \
		sources/my_isneg.c \
		sources/my_is_prime.c \
		sources/my_putchar.c \
		sources/my_put_nbr.c \
		sources/my_putnbr_base.c \
		sources/my_putstr.c \
		sources/my_revstr.c \
		sources/my_showmem.c \
		sources/my_showstr.c \
		sources/my_show_word_array.c \
		sources/my_sort_int_array.c \
		sources/my_strcapitalize.c \
		sources/my_strcat.c \
		sources/my_strcmp.c \
		sources/my_strcpy.c \
		sources/my_str_isalpha.c \
		sources/my_str_islower.c \
		sources/my_str_isnum.c \
		sources/my_str_isprintable.c \
		sources/my_str_isupper.c \
		sources/my_strlen.c \
		sources/my_strlowcase.c \
		sources/my_strncat.c \
		sources/my_strncmp.c \
		sources/my_strncpy.c \
		sources/my_strstr.c \
		sources/my_str_to_word_array.c \
		sources/my_strupcase.c \
		sources/my_swap.c \
		sources/my_strdup.c \
		sources/my_putstr_e.c \
		sources/printf.c \
		sources/my_putnbr_base_long.c \
		sources/my_putstr_e.c \
		sources/my_arrlen.c \
		sources/my_get_digit.c \
		sources/my_realloc.c \
		sources/my_str_is_alphanum.c \
		sources/my_strchr.c \
		sources/my_atoi.c

OBJ = $(SRC:%.c=%.o)

TESTS = tests/test_my_printf.c \

SRC_TEST =	sources/my_putnbr_base_long.c \
	  		sources/my_putstr.c \
			sources/my_put_nbr.c \
			sources/my_putstr_e.c \
			sources/printf.c \
			sources/my_putchar.c \
			sources/my_putnbr_base.c \
			sources/my_strlen.c \

INCLUDE = -I ./include

COVERAGE = --coverage -lcriterion

CFLAGS = -W -Wall -Wextra -Wshadow

CC = gcc

NAME_TEST = unit_tests

all : $(NAME)

$(NAME) : $(OBJ)
	$(AR) rc $(NAME) $(OBJ)

clean :
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)
	$(RM) *.gc*
	$(RM) $(NAME_TEST)

re : fclean all

dbg: CFLAGS += -g
dbg: re

tests_run :
	$(RM) *.gc*
	$(CC) -o $(NAME_TEST) $(SRC_TEST) $(TESTS) $(INCLUDE) $(COVERAGE) $(CFLAGS)
	./unit_tests
