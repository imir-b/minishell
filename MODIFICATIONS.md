# Modifications apportées à Minishell

Ce document récapitule les changements effectués pour assurer la compatibilité avec le `minishell_tester`.

## 1. Mode Interactif vs Non-Interactif
- **Fichiers :** `src/main.c`, `src/process.c`, `inc/minishell.h`
- **Action :** Détection automatique du mode terminal via `isatty(STDIN_FILENO)`.
- **Impact :** 
  - Désactivation de la bannière ASCII et du prompt en mode non-interactif.
  - Utilisation de `get_next_line` au lieu de `readline` pour éviter l'écho des commandes.

## 2. Codes de sortie et erreurs
- **Fichier :** `src/exec/exec.c`
- **Action :** 
  - Gestion des erreurs `is a directory` (code 126).
  - Gestion des commandes introuvables (code 127).
  - Distinction entre échec d'accès et fichier manquant.

## 3. Redirections multiples
- **Fichiers :** `src/exec/exec_redir.c`, `src/parsing/ast/redir_node.c`, `inc/parsing.h`
- **Action :** 
  - Refonte de la structure de l'AST pour les redirections. Les redirections sont maintenant chaînées et traitées séquentiellement avant l'exécution de la commande.
  - `ft_exec_redir` boucle désormais sur toute la chaîne de redirections.
- **Impact :** Correction de la gestion de plusieurs redirections sur une même ligne (ex: `ls > f1 > f2`).

## 4. Nettoyage de la mémoire
- **Fichier :** `src/parsing/ast/free_ast.c`
- **Action :** Mise à jour de `ft_free_ast` pour supporter la nouvelle structure chaînée.
