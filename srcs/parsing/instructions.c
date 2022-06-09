/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahouari <ahouari@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/05 08:29:06 by ahouari           #+#    #+#             */
/*   Updated: 2022/06/05 08:29:06 by ahouari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** 🦕🌴
**
** get_instructions
**
**	This function is a ft_split tailored to minishell.
**		It takes into account quotes and divides the given
**		string into chuncks according to a delimiter ('|').
**
**	Since open quotes are undefined behaviour, we save
**	everything following the quote as if we were waiting for
**	the user to close the quote (which is what bash does).**	
** 		for example:
** 			> ls -l | echo hello
**				ls -l
**				echo hello
** 			> ls -l " | echo hello
**				ls -l " | echo hello
**
** 🌴🥥
*/

static	int	nb_words(const char *s, char c)
{
	int		i;
	int		nb;
	char	quote;

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

static int	get_nb_letters(const char *s, int i, char c, char quote)
{
	int		letters;

	letters = 0;
	while (s[i + letters] && ((s[i + letters] != c && !quote) || quote))
	{
		quote = check_quote(s[i + letters], quote);
		letters++;
	}
	return (letters);
}
/*
static	char	**fill_instructions(
					const char *s, char c, int words, char **split)
{
	int		i;
	int		word;
	int		letters;
	char	quote;

	i = 0;
	word = 0;
	quote = 0;
	while (word < words)
	{
		// if (s[0] == PIPE || s[0] == '<')
		// {
		// 	if (s[0] == PIPE)
		// 		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
		// 	else
		// 		ft_putstr_fd("minishell: No such file or directory\n", 2);
		// 	return (NULL);
		// }
		while (s[i] && s[i] == c)
			i++;
		letters = get_nb_letters(s, i, c, quote);
		split[word] = ft_substr(s, i, letters);
		word++;
		i += letters;
	}
	split[word] = 0;
	return (split);
}
*/

static	int	check(char s0, char s1)
{
	if (s0 == PIPE || (s0 == '<' && s1 != '<'))
	{
		if (s0 == PIPE)
			ft_putstr_fd("minishell: syntax error near unexpected token `|'\n",
				2);
		else
			ft_putstr_fd("minishell: No such file or directory\n", 2);
		return (1);
	}
	return (0);
}

static	char	**fill_instructions(
					const char *s, char c, int words, char **split)
{
	int		i;
	int		j;
	int		word;
	int		letters;
	char	quote;

	i = 0;
	word = 0;
	quote = 0;
	while (word < words)
	{
		if (check(s[0], s[1]))
			return (NULL);
		while (s[i] && s[i] == c)
			i++;
		letters = get_nb_letters(s, i, c, quote);
		split[word] = calloc_or_exit(sizeof(char), letters + 1);
		j = 0;
		while (s[i] && j < letters)
			split[word][j++] = s[i++];
		split[word++][j] = 0;
	}
	split[word] = 0;
	return (split);
}

char	**get_instructions(const char *s, char c)
{
	int		words;
	char	**split;

	if (!s)
		return (NULL);
	words = nb_words(s, c);
	split = calloc_or_exit(sizeof(char *), words + 1);
	fill_instructions(s, c, words, split);
	return (split);
}
