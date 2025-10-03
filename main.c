/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdheen <mdheen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:58:59 by mdheen            #+#    #+#             */
/*   Updated: 2025/10/03 18:51:10 by mdheen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_dupstdin;

bool	add_to_history(const char *line)
{
	if (line[0] != '\0')
	{
		add_history(line);
		return (true);
	}
	else
	{
		ft_close(&g_dupstdin);
		ft_free(&line);
		return (false);
	}
}

bool	handle_tokenization_error(t_shell *shell, bool success, char *line)
{
	if (success == false)
	{
		shell->last_exit_code = 258;
		ft_lstclear(&shell->tokens, free_token);
		ft_close(&g_dupstdin);
		ft_free(&line);
		return (false);
	}
	return (true);
}

bool	handle_parsing_error(t_shell *shell, bool success, char *line)
{
	if (success == false || check_subexprs(shell, shell->steps) == false)
	{
		shell->last_exit_code = 258;
		ft_stderr("Parse error\n");
		ft_lstclear(&shell->tokens, free_token);
		free_steps(&shell->steps_to_free);
		rl_on_new_line();
		ft_close(&g_dupstdin);
		ft_free(&line);
		return (false);
	}
	return (true);
}

static void	read_and_tokenize(t_shell *shell)
{
	char	*line;
	bool	success;

	while (1)
	{
		line = minishell_readline(shell);
		if (!line)
			continue ;
		if (add_to_history(line) == false)
			continue ;
		success = true;
		shell->tokens = tokenize_line(shell, line, &success);
		if (handle_tokenization_error(shell, success, line) == false)
			continue ;
		shell->steps = parse_tokens(shell->tokens, &success);
		ft_lstadd_back(&shell->steps_to_free, ft_lstnew(shell->steps));
		if (handle_parsing_error(shell, success, line) == false)
			continue ;
		minishell_run_heredocs(shell);
		if (handle_heredoc_ctrl_c(shell, line) == false)
			continue ;
		minishell_exec_and_cleanup(shell, line);
	}
}

int	main(int argc, char **argv, char **env)
{
	t_shell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, env);
	disable_echoctl();
	read_and_tokenize(&shell);
	return (0);
}
