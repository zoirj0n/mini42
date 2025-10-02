/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoisobir <zoisobir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 18:15:15 by zoisobir          #+#    #+#             */
/*   Updated: 2025/10/01 18:15:16 by zoisobir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	erase_environment_entry(t_shell *shell, char **env_copy, char *to_look)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (shell->env[i] != NULL)
	{
		if (ft_strncmp(shell->env[i], to_look, ft_strlen(to_look)) != 0)
			env_copy[j++] = shell->env[i++];
		else
			deallocate_memory(&shell->env[i++]);
	}
}

void	erase_declared_entry(t_shell *shell, char **env_copy, char *to_look)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (shell->declared_env[i] != NULL)
	{
		if (ft_strncmp(shell->declared_env[i], to_look,
				ft_strlen(to_look)) != 0)
			env_copy[j++] = shell->declared_env[i++];
		else
			deallocate_memory(&shell->declared_env[i++]);
	}
}
