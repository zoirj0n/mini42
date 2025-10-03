/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_operator.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdheen <mdheen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:57:13 by mdheen            #+#    #+#             */
/*   Updated: 2025/10/03 17:07:28 by mdheen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_operator(const char *line, const size_t i)
{
	if ((line[i] == '>' && line[i + 1] != '>') || (line[i] == '<'
			&& line[i + 1] != '<') || (line[i] == '<' && line[i + 1] == '<')
		|| (line[i] == '>' && line[i + 1] == '>') || (line[i] == '|'
			&& line[i + 1] != '|') || (line[i] == '&' && line[i + 1] == '&')
		|| (line[i] == '|' && line[i + 1] == '|'))
		return (true);
	return (false);
}

t_list	*tokenize_operator(const char *line, size_t *idx,
		const t_token_type type)
{
	t_token	*token;
	t_list	*el;

	token = ft_calloc(1, sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->start = *idx;
	token->type = type;
	token->end = *idx;
	if (type == HEREDOC || type == APPEND || type == LAST_EXIT || type == AND
		|| type == OR)
	{
		token->end++;
		token->substr = ft_substr(line, token->start, 2);
	}
	else
		token->substr = ft_substr(line, token->start, 1);
	el = ft_lstnew(token);
	if (token->substr == NULL || el == NULL)
		return (NULL);
	if (type == HEREDOC || type == APPEND || type == LAST_EXIT || type == AND
		|| type == OR)
		*idx += 1;
	return (el);
}
