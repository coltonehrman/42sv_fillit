/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cehrman <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 19:15:53 by cehrman           #+#    #+#             */
/*   Updated: 2020/02/20 19:40:38 by cehrman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list *lst;
	t_list *tmp;

	if (!alst || !(*alst))
		return ;
	lst = *alst;
	while (lst)
	{
		tmp = lst->next;
		del(lst->content, lst->content_size);
		free(lst);
		lst = tmp;
	}
	*alst = 0;
}
