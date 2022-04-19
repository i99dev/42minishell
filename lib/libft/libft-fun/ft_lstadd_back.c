/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 06:10:38 by oal-tena          #+#    #+#             */
/*   Updated: 2021/10/11 06:12:12 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*obj;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		obj = ft_lstlast(*lst);
		obj->next = new;
	}
	new = ft_lstlast(*lst);
	new->next = NULL;
}
