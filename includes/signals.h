/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdheen <mdheen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 18:52:06 by zoisobir          #+#    #+#             */
/*   Updated: 2025/10/03 18:55:05 by mdheen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

void	handle_eof(const char *line, t_shell *shell);
void	handle_ctrl_c(t_shell *shell);
bool	handle_heredoc_ctrl_c(t_shell *shell, char *line);

#endif
