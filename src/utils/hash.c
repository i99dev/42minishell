/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 14:15:58 by oal-tena          #+#    #+#             */
/*   Updated: 2022/04/22 15:07:43 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief h_hash function return the hash of the string index.
 * 
 * @param str hash name or key
 * @return unsigned int  index insiad table
 */

unsigned int	h_hash(char *str)
{
	return ft_strlen(str);
}