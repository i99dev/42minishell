/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oal-tena <oal-tena@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 12:12:55 by oal-tena          #+#    #+#             */
/*   Updated: 2022/04/25 13:37:44 by oal-tena         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

typedef struct s_token
{
	char			*token;
	int				type;
	struct s_token	*next;
}					t_token;

void	ft_tokenizer(char *str, t_token *table);

#endif