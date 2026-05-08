# Résolution du Segfault lors des Redirections

Ce document explique les modifications apportées pour corriger le crash (Segmentation Fault) survenant lors de l'utilisation de redirections sans commande (ex: `<< a`).

## 1. Correction du Segfault Principal

### Emplacement : `src/parsing/tokenize.c`
**Problème :** La fonction `ft_token_last` tentait d'accéder à `first->next` sans vérifier si `first` était `NULL`. Lorsqu'une redirection est la seule chose sur la ligne, le parser extrait tous les tokens restants, laissant une liste vide (`NULL`).

**Solution :** Ajout d'une vérification `if (!first) return (NULL);`.

```c
t_token	*ft_token_last(t_token *first)
{
	t_token	*last;

	/* Correction : Retourne NULL si la liste est vide au lieu de crash */
	if (!first)
		return (NULL);
	last = first;
	while (last->next)
		last = last->next;
	return (last);
}
```

## 2. Correction de l'Expansion des Redirections Chaînées

### Emplacement : `src/exec/exec_redir.c`
**Problème :** Seul le premier maillon d'une chaîne de redirections était expansé (ex: dans `> $VAR1 > $VAR2`, seul `$VAR1` était traité).

**Solution :** Déplacement de l'appel à `ft_expand_node` à l'intérieur de la boucle `while` de `ft_apply_all_redirs`.

```c
static int	ft_apply_all_redirs(t_ast **node, t_hash_table *map)
{
	int	fd;

	while (*node && (*node)->type >= NODE_REDIR_IN
		&& (*node)->type <= NODE_HEREDOC)
	{
		/* Correction : Expande chaque fichier de redirection dans la boucle */
		if (ft_expand_node(*node, map))
			return (1);
		fd = ft_open_file(*node);
		// ... reste du code
	}
}
```

## 3. Nettoyage de la Logique d'Exécution

### Emplacement : `src/exec/exec.c`
**Modification :** Retrait de l'expansion redondante de la première redirection puisque `ft_exec_redir` s'en occupe maintenant de manière exhaustive pour toute la chaîne.

```c
	if (node->type >= NODE_REDIR_IN && node->type <= NODE_HEREDOC)
	{
		/* On passe directement à l'exécution de la redirection
		   qui gérera elle-même ses expansions. */
		return (ft_exec_redir(node, data));
	}
```

---
*Document généré suite à l'investigation du bug.*
