/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:36:04 by npetitpi          #+#    #+#             */
/*   Updated: 2023/11/15 10:21:19 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_export(t_info *cmd, t_list **envl)
{
	if (nb_args(cmd->argv + cmd->offset) <= 1)
		return (print_sorted(*envl, cmd));
	if (!cmd->is_subprocess)
		return (export_all(cmd->argv + cmd->offset + 1, envl, 2));
	else
		return (SUCCESS);
}
