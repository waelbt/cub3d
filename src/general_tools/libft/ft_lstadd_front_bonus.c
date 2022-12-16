/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: waboutzo <waboutzo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 01:49:04 by waboutzo          #+#    #+#             */
/*   Updated: 2022/12/16 19:26:04 by waboutzo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft.h"

void	ft_lstadd_front(t_list **list, t_list *new)
{
	new->next = *list;
	*list = new;
}

/*
#include <stdio.h>
void printflinklist(t_list *head)
{
	t_list *temporary = head;
    while(temporary != NULL)
    {
        printf("%s - ",(char *)temporary->content);
        temporary = temporary->next;
    }
    printf("\n");
}
int main(void)
{
	t_list *list = NULL;
	t_list *tmp;
	
	tmp = ft_lstnew("dadadd");
	tmp->next = list;
	list = tmp;
	tmp = ft_lstnew("wael");
	tmp->next = list;
	list = tmp;
	tmp = ft_lstnew("walid");
	tmp->next = list;
	list = tmp;
	ft_lstadd_front(&list, ft_lstnew("test"));
	printflinklist(list);	
}
*/