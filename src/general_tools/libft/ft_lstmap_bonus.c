/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 01:48:00 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/16 19:26:04 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"
/*
#include <stdio.h>

void del(void *t)
{
	free(t);
}
void *fun(void *t)
{
	*(char *)t -= 32;
	return t;
}
*/

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*tmp;

	if (!lst)
		return (0);
	newlst = NULL;
	while (lst)
	{
		tmp = ft_lstnew(f(lst->content));
		if (!tmp)
		{
			ft_lstclear(&tmp, del);
			return (0);
		}
		ft_lstadd_back(&newlst, tmp);
		lst = lst->next;
	}
	return (newlst);
}

/*
int main(void)
{
	t_list *retmp;
	t_list *head = NULL;
	t_list *tmp;
	
	char s[] = "dadad";
	char d[] = "wee";
	tmp = ft_lstnew(s);
	tmp->next = head;
	head = tmp;
	tmp = ft_lstnew(d);
	tmp->next = head;
	head = tmp;
	retmp = ft_lstmap(head, fun, del);
	while(head)
	{
		printf("%s\n", head->content);
		head = head->next;
	}
}
*/
