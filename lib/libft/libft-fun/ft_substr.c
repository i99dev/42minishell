/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dokcer <Dokcer@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 08:50:49 by oal-tena          #+#    #+#             */
/*   Updated: 2022/07/13 15:04:05 by Dokcer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;
	char	*temp;

	i = ft_strlen(s);
	if (len + start > i)
		len = ft_strlen(s);
	if (start >= i)
	{
		str = malloc(sizeof(char));
		*str = '\0';
		return (str);
	}
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	temp = str;
	i = 0;
	while (*(s + start) && i++ < len)
	{
		*str++ = *(s + start);
		start++;
	}
	*str = '\0';
	return (temp);
}
