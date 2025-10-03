/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoisobir <zoisobir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:55:50 by mdheen            #+#    #+#             */
/*   Updated: 2025/10/03 21:14:58 by zoisobir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_interactive(int sig)
{
	int	ret;

	ret = waitpid(-1, NULL, WNOHANG);
	if (sig == SIGINT && ret == -1)
	{
		write(2, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		ft_close(&g_dupstdin);
	}
}

void	sigint_command(int sig)
{
	int	ret;

	ret = waitpid(-1, NULL, WNOHANG);
	if (sig == SIGINT)
	{
		if (ret == -1)
		{
			write(2, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
}

void	sigquit_command(int sig)
{
	if (sig == SIGQUIT)
	{
	}
}

void	hd_sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_close(&g_dupstdin);
		get_next_line(-1);
		rl_on_new_line();
		printf("\n");
	}
}
