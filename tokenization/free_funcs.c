/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_funcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdheen <mdheen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:56:50 by mdheen            #+#    #+#             */
/*   Updated: 2025/10/03 16:56:50 by mdheen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free(void *memory)
{
	if (*(void **)memory != NULL)
		free(*(void **)memory);
	*(void **)memory = NULL;
}

void	free_token(void *mem)
{
	t_token	*token;

	token = mem;
	ft_free(&token->substr);
	if (token->sub_tokens != NULL)
		ft_lstclear(&token->sub_tokens, free_token);
	ft_free(&token);
}

void	free_split_array(char **split)
{
	size_t	i;

	if (split == NULL)
		return ;
	i = 0;
	while (split[i] != NULL)
	{
		ft_free(&split[i]);
		i++;
	}
	ft_free(&split);
}
