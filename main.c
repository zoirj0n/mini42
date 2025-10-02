/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoisobir <zoisobir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:03:04 by zoisobir          #+#    #+#             */
/*   Updated: 2025/10/02 19:03:07 by zoisobir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_dupstdin;

void	init_shell(t_shell *shell, char **env)
{
	char	*shelvl_env;
	char	*shlvl_str;

	shell->env = duplicate_string_array(env);
	shell->declared_env = NULL;
	shell->steps_to_free = NULL;
	delete_variable(shell, "OLDPWD");
	modify_declared_variable(shell, "OLDPWD");
	shelvl_env = retrieve_environment_variable(shell, "SHLVL");
	shell->fd = ft_calloc(2, sizeof(int));
	if (shell->fd == NULL)
	{
		release_string_array(shell->env);
		deallocate_memory(&shelvl_env);
		exit(EXIT_FAILURE);
	}
	if (shelvl_env != NULL)
	{
		shlvl_str = join_and_free_strings("SHLVL=", ft_itoa(ft_atoi(shelvl_env)
					+ 1), 2);
		modify_environment_variable(shell, shlvl_str);
		deallocate_memory(&shlvl_str);
		deallocate_memory(&shelvl_env);
	}
	shell->last_exit_code = 0;
}

bool	add_to_history(const char *line)
{
	if (line[0] != '\0')
	{
		add_history(line);
		return (true);
	}
	else
	{
		close_descriptor(&g_dupstdin);
		deallocate_memory(&line);
		return (false);
	}
}

bool	handle_tokenization_error(t_shell *shell, bool success, char *line)
{
	if (success == false)
	{
		shell->last_exit_code = 258;
		ft_lstclear(&shell->tokens, release_token_memory);
		close_descriptor(&g_dupstdin);
		deallocate_memory(&line);
		return (false);
	}
	return (true);
}

bool	handle_parsing_error(t_shell *shell, bool success, char *line)
{
	if (success == false || validate_subexpressions(shell,
			shell->steps) == false)
	{
		shell->last_exit_code = 258;
		ft_stderr("Parse error\n");
		ft_lstclear(&shell->tokens, release_token_memory);
		release_execution_steps(&shell->steps_to_free);
		rl_on_new_line();
		close_descriptor(&g_dupstdin);
		deallocate_memory(&line);
		return (false);
	}
	return (true);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	bool	success;
	t_shell	shell;

	(void)argc;
	(void)argv;
	init_shell(&shell, env);
	while (1)
	{
		line = read_command_line(&shell);
		if (add_to_history(line) == false)
			continue ;
		success = true;
		shell.tokens = process_input_line(&shell, line, &success);
		if (handle_tokenization_error(&shell, success, line) == false)
			continue ;
		shell.steps = analyze_token_stream(shell.tokens, &success);
		ft_lstadd_back(&shell.steps_to_free, ft_lstnew(shell.steps));
		if (handle_parsing_error(&shell, success, line) == false)
			continue ;
		process_heredoc_inputs(&shell);
		if (process_heredoc_interrupt(&shell, line) == false)
			continue ;
		execute_and_cleanup_shell(&shell, line);
	}
}
