# Récapitulatif des changements : Gestion des variables locales

Ce document récapitule les modifications apportées pour ajouter le support des variables locales (non exportées) dans minishell.

## 1. Modifications de la structure de données
- **Fichier : `inc/data.h`**
  - Ajout du champ `int is_exported` à la structure `s_env_node`. Ce flag permet de distinguer les variables d'environnement (exportées) des variables locales au shell.

## 2. Gestion de la table de hachage
- **Fichier : `src/parsing/expand/hash.c`**
  - Mise à jour de `ft_fill_item` pour accepter et stocker le flag `is_exported`.
  - Mise à jour de `ft_init_hash_map` pour marquer toutes les variables issues de `envp` comme exportées (`is_exported = 1`).
  - Ajout de la fonction `ft_find_env_node` pour récupérer un noeud complet de la table (nécessaire pour modifier son flag d'exportation).
  - Déplacement de la fonction `ft_is_valid_key` (depuis `export.c`) pour centraliser la validation des identifiants.

## 3. Mise à jour des Built-ins
- **Fichier : `src/exec/built-in/export.c`**
  - Mise à jour de `ft_hash_table_insert` pour accepter le flag `export_flag`.
  - Mise à jour de `ft_export_single` pour gérer le cas `export VAR` (sans valeur), qui marque désormais une variable existante comme exportée.
  - Mise à jour de `ft_print_export` pour utiliser le nouveau mécanisme de filtrage (via `ft_get_env_tab`).
- **Fichier : `src/exec/built-in/env.c`**
  - Modification de `ft_env` pour n'afficher que les variables ayant le flag `is_exported` à 1.
- **Fichier : `src/exec/built-in/cd.c`**
  - Mise à jour des appels à `ft_hash_table_insert` pour préserver le statut d'exportation de `PWD` et `OLDPWD`.

## 4. Logique d'exécution et assignations
- **Fichier : `src/exec/exec.c`**
  - Ajout de la détection des assignations en préfixe de commande (ex: `VAR=1 echo hello`).
  - Gestion des assignations seules (ex: `VAR=1`) : elles sont désormais stockées de manière persistante dans le shell comme variables locales.
  - Gestion des assignations avec commande externe : elles sont ajoutées à l'environnement passé à `execve` via un fork.
  - **Correction de bug (Crash)** : Utilisation de pointeurs temporaires pour décaler `args` sans corrompre le pointeur original utilisé pour libérer la mémoire de l'AST (`free(): invalid pointer`).
- **Fichier : `src/exec/exec_utils.c`**
  - Mise à jour de `ft_get_env_tab` et `ft_count_env` pour ne retourner que les variables exportées. Cela garantit que les processus enfants ne reçoivent que les variables d'environnement réelles.

## 5. Modifications des Headers
- **Fichier : `inc/parsing.h`**
  - Mise à jour des prototypes pour inclure les nouveaux paramètres (`export_flag`) et les nouvelles fonctions utilitaires.

---
**Exemple d'usage :**
- `VAR=1` : Définit une variable locale `VAR`. Elle n'apparaît pas dans `env`.
- `echo $VAR` : Affiche `1`.
- `export VAR` : Rend `VAR` visible dans `env`.
- `VAR=2 echo $VAR` : Utilise `VAR=2` temporairement pour la commande.
