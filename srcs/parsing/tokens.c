/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 08:29:06 by ahouari           #+#    #+#             */
/*   Updated: 2022/06/05 08:30:29 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** 🦕🌴
**
** get_tokens
**
**	This function gets all the individual tokens.
**		examples:
**			hello
**			hello"this'"is""wo'rld"!
**			"he   llo",you
**
**	1. Get the right number of tokens to allocate the right amount of memory.
**	2. Using spaces as delimiters, fill up the struct with the words while
**		taking quotes into account.
**	This function is quite smiliar to ft_split, but tailored to minishell.
**
** 🌴🥥
*/

int	get_nb_tokens(const char *s, char c)
{
	int			i;
	int			nb;
	char		quote;

	i = 0;
	nb = 0;
	quote = 0;
	while (s[i])
	{
		quote = check_quote(s[i], quote);
		if (s[i] != c && (s[i + 1] == 0 || (s[i + 1] == c && !quote)))
				nb++;
		i++;
	}
	return (nb);
}

static int	get_token_len(const char *s, int i, char c)
{
	int		letters;
	char	quote;

	quote = 0;
	letters = 0;
	while (s[i + letters] && ((s[i + letters] != c && !quote) || quote))
	{
		quote = check_quote(s[i + letters], quote);
		letters++;
	}
	return (letters);
}

static t_token	*fill_tokens(const char *s, char c, int words, t_token *tokens)
{
	int		i;
	int		j;
	int		word;
	int		letters;

	i = 0;
	word = 0;
	while (word < words && s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		letters = get_token_len(s, i, c);
		tokens[word].text = calloc_or_exit(sizeof(char), letters + 1);
		j = 0;
		while (s[i] && j < letters)
			tokens[word].text[j++] = s[i++];
		tokens[word++].text[j] = 0;
	}
	return (tokens);
}

t_token	*get_tokens(const char *s, char c, int words)
{
	t_token	*tokens;

	if (!s)
		return (NULL);
	tokens = calloc_or_exit(sizeof(t_token), words + 1);
	fill_tokens(s, c, words, tokens);
	return (tokens);
}
