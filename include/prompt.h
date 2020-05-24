/*
** EPITECH PROJECT, 2020
** ash
** File description:
** prompt
*/

#ifndef PROMPT_H_
#define PROMPT_H_

char *prompt_attr(int attr, bool off);
char *minimal_hostname(char *hostname);
char *date_format(int date);
char *str_tolower(char *str);

char *get_prompt_value(char c, env_t *env);

#endif /* !PROMPT_H_ */