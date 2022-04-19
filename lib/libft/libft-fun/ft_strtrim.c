/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 05:45:57 by oal-tena          #+#    #+#             */
/*   Updated: 2021/10/09 04:21:07 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*str;
	int		i;

	start = 0;
	i = 0;
	if (!s1 || !set)
		return (NULL);
	end = ft_strlen((char *)s1);
	while (ft_strchr((char *)set, s1[start]) && s1[start])
		start++;
	while (s1[start] != 0
		&& ft_strchr((char *)set, s1[end - 1]) && end != start)
		end--;
	str = ft_substr((char *)s1, start, end - start);
	return (str);
}
