/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 11:59:42 by oal-tena          #+#    #+#             */
/*   Updated: 2021/10/04 12:23:59 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*str;
	unsigned char	*str1;

	str = (unsigned char *)s1;
	str1 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (str[i] == str1[i] && i < n - 1)
		i++;
	return (str[i] - str1[i]);
}
