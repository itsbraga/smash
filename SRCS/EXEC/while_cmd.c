/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   while_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: art3mis <art3mis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 18:50:27 by pmateo            #+#    #+#             */
/*   Updated: 2024/09/27 22:56:35 by art3mis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parent()
{
	
}

void	while_cmd(t_exec_lst **e_lst, t_exec_info *e_info, t_env_lst **env)
{
	t_exec_lst *node;
	char **envtab;

	node = *e_lst;
	envtab = recreate_env_tab(env);
	while (e_info->executed_cmd != e_info->cmd_count && node != NULL)
	{
		if (e_info->pipe_count)
			if (pipe(e_info->fd) == -1)
				clean_exit();
		e_info->child_pid = fork();
		if (e_info->child_pid == -1)
			clean_exit();
		if (!e_info->child_pid)
			pathfinder(node, node->redir, e_info, envtab);
		else
			parent();
		node = node->next;
		e_info->executed_cmd++;
	}	
}

//NOTES :
// - Je dois reperer la presence de pipe, et ne surtout pas en ouvrir si il n'y
//		en a pas.
// - cas d'erreur lorsque chemin relatif et que $PATH n'existe pas
// - Si un segment de commande echoue le message d'erreur ne s'affiche qu'apres
		// l'execution de TOUTE la commande, dans l'ordre des erreurs rencontre.
// - Les heredocs sont ecrits avant toutes choses, et lus au moment du traitement
//		de la commande.
// - Je dois connaitre le nombre exact de here_doc dans une commande
// - Pour les here_doc, besoin de deux fonctions, une principale qui bouclera selon
//		le nombre de here_doc, une seconde qui s'occupe du prompt, et de remplir le fd.
// - ouvrir un pipe -> ecrire dans fd[1] -> fermer fd[1] -> rediriger fd[0] vers STDIN ->
// 		fermer fd[0], rebellotte avec le nombre de here_doc