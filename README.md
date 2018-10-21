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

Dans mon groupe de projet, nous avons remarqué que la fonction find permettait de répéter certaines options. Par exemple, si le dossier courant ne contient qu'un fichier nommé "toto.txt", la commande "find toto.txt -print" affiche "toto.txt", alors que la commande "find toto.txt -print -print" (le "-print" est répété) affiche "toto.txt" suivi d'un retour à la ligne puis un deuxième "toto.txt". Quel est le comportement attendu pour rsfind ?

Dans notre cas on pourra se limiter à un affichage unique, je vous ai demandé d'utiliser la fonction getopt qui parse la ligne d'options, il est vraisemblable que la commande find implante quelque chose de plus complexe en analysant intégralement toute la ligne d'arguments pour chaque fichier qu'elle découvre. Implanter un tel comportement serait très compliqué et hors du cadre d'un projet de découverte des aspects réseau et système, il ne sera donc pas demandé de le faire.

Dans le sujet il est marqué que la commande : rsfind DOSSIER -exec "COMMANDE" doit effectuer la même action que find DOSSIER -exec COMMANDE \ ;
Est-ce cela exactement ou ne manque-t-il pas {} avant le \; ?
C'est-à-dire, est ce que la commande ”COMMANDE” doit être appelée par rsfind avec comme dernier paramètre les occurrences trouvées par le find, pour que la commande "COMMANDE" soit exécutée sur chaque résultat trouvé par le find ? 
J'ai remarqué que sinon, si on le fait comme écrit dans le sujet, cela effectue la commande  "COMMANDE" à l'identique autant de fois qu'il y a d'éléments dans le dossier DOSSIER.


Il est évidemment nécessaire de faire apparaître des accolades dans la commande passée en paramètre, simplement comme celles-ci peuvent figurer à différents endroits il ne m'a pas semblé opportun de les indiquer, le sujet vous demande en effet d'utiliser des pipes et ceci vous demandera d'intégrer des accolades avant la fin de la commande.