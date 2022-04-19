/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 11:24:46 by oal-tena          #+#    #+#             */
/*   Updated: 2021/10/04 11:54:58 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	char			*s;

	s = (char *)str;
	while (n > 0)
	{
		if (*s == (char)c)
		{
			return ((char *)s);
		}
		s++;
		n--;
	}
	return (0);
}
