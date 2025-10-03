/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checket_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zoisobir <zoisobir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 18:14:36 by zoisobir          #+#    #+#             */
/*   Updated: 2025/10/03 18:21:57 by zoisobir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    check_handler_tokenization_err(t_shell *shell, bool success, char *line)
{
    if (handle_tokenization_error(&shell, success, line) == false)
        continue ;
}
void    check_handler_parsing_err(t_shell *shell, bool success, char *line)
{
    if (handle_parsing_error(&shell, success, line) == false)
        continue ;
}
void    check_heredoc_ctrl_c(t_shell *shell, char *line)
{
    if (handle_heredoc_ctrl_c(&shell, line) == false)
        continue ;
}
void    check_history(char *line)
{
    if (add_to_history(line) == false)
        continue ;
}