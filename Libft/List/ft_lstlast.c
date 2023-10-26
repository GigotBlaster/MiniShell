/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:25:52 by npetitpi          #+#    #+#             */
/*   Updated: 2023/10/26 13:25:53 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*beg;

	beg = lst;
	while (beg && beg->next)
		beg = beg->next;
	return (beg);
}
