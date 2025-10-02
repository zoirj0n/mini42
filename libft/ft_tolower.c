/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdheen <mdheen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:23:30 by mdheen            #+#    #+#             */
/*   Updated: 2025/10/02 19:23:31 by mdheen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	int	uppercase_diff;

	uppercase_diff = 'a' - 'A';
	if (c >= 'A' && c <= 'Z')
		return (c + uppercase_diff);
	return (c);
}
