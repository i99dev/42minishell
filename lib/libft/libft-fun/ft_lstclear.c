/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 06:18:41 by oal-tena          #+#    #+#             */
/*   Updated: 2021/10/11 06:20:18 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*x;
	t_list	*y;

	if (!del)
		return ;
	x = *lst;
	while (x)
	{
		y = x;
		x = x->next;
		del(y->content);
		free(y);
	}
	*lst = NULL;
}
