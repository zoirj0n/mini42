/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdheen <mdheen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:54:11 by mdheen            #+#    #+#             */
/*   Updated: 2025/10/03 16:54:12 by mdheen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	int	uppercase_diff;

	uppercase_diff = 'a' - 'A';
	if (c >= 'a' && c <= 'z')
		return (c - uppercase_diff);
	return (c);
}
