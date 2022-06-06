/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/06 14:43:08 by oal-tena          #+#    #+#             */
/*   Updated: 2022/06/06 14:45:02 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	error_message(t_minishell *msh, char *error_message, int status)
{
	ft_putendl_fd(error_message, 2);
	msh->exit_status = status;
}
