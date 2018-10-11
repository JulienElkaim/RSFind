Questions / réponses sur le projet de RS :

Je ne sais pas où trouver le dépôt rs2018-template :

Coquille du sujet, utiliser rs2018 comme dépôt template


Je ne vois pas le fichier yml dans le dépôt :

Il n'y a pas de fichier yml au projet de cette année, libre à vous d'en ajouter un ou bien de mettre vos tests unitaires dans un fichier yml que vous créeriez vous-même.

Suite à quelques hésitations sur le sujet voilà quelques questions:

- La librairie dirent.h est-elle autorisée pour l'implémentation? 

La librairie dirent.h est non seulement autorisée mais attendue, toute librairie de la bibliothèque standard que vous pouvez utiliser sans avoir à l'installer est autorisée. 

- Les commandes d'exécution C (execvp) sont-elles autorisées ?

Oui dans le cas de l'option --exec, c'est l'utilisation de la fonction excvp pour exécuter les commandes shell fournies dans le sujet qui est prohibée.

on retrouve plusieurs fois dans le sujet l'option --print mais je n'ai pas trouver se que doit faire cette option précisément. 

L'option --print demande l'affichage des fichiers trouvés par rsfind, de la même manière que l'option -print de la commande find.
Je voulais également savoir si l'utilisation de printf étais possible étant donnée qu'une option --print est demandée.

Utilisez plutôt la commande write et la sortie standard (file descriptor 1) pour implanter cette fonctionnalité, ce n'est pas très compliqué et ce sera plus en lien avec le cours de RS.