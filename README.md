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

Nous sommes actuellement entrain de le projet en faisant bloc par bloc les différentes fonctionnalités avant de tout regrouper ensemble. J'aimerai juste savoir si la liste des bibliothèques ci-dessous sont toutes autorisées, pour continuer à travailler efficacement et dans la légalité. Je n'ai pas eu à les installer donc je présume que c'est ok mais je préfère demander pour ne pas avoir de surprises : errno.h, stdio.h, string.h, sys\types.h, unistd.h, dirent.h, err.h, stddef.h, sys\stat.h.

Ces librairies sont toutes nativement installées sur votre machine, vous êtes donc en droit de les utiliser, vous êtes en revanche invités à privilégier l'utilisation des fonctions read et write pour vos affichages et lectures en ligne de commande, l'utilisation de ces fonctions sera valorisée par rapport à l'utilisation de printf et scanf qui sont de plus haut niveau.



Ayant créé le Gitlab aujourd'hui, j'ai cru comprendre que la méthode que nous utilisons pour exec était illégale à cause de l'emploi d'execvp. Cependant, pour éviter toute ambiguité, pourriez-vous s'il-vous-plaît me le confirmer, auquel cas nous ne savons vraiment pas comment faire.

Voici le code utilisé

void execCmdOnFile_aux(int inFd, int outFd, char ** cmd, int* childProcCnt){    
    if(!fork()){
        dup2(inFd, 0);
        dup2(outFd, 1);
        execvp(cmd[0], cmd);        
    }else{
        (*childProcCnt)++;
    }
}

Cette utilisation de execvp est on ne peut plus légale, c'est l'utilisation d'execvp pour exécuter directement les commandes indiquées dans le sujet qui est prohibée en raison du fait qu'il serait considéré comme une tricherie d'utiliser des binaires de votre système au lieu d'implanter les fonctionnalités demandées dans le sujet par vous-mêmes.

1) Peut on utiliser la bibliothèque sys/stat.h pour accéder aux informations nécessaires pour l'option -l (permissions etc), si non, quelle est l'alternative ? 

Oui, toute bibliothèque installée par défaut sur votre machine est utilisable.


2) Avec la fonction find, on peut par exemple taper find *.c pour avoir uniquement les fichiers terminant par C. Qu'est-il attendu pour la fonction rsfind lorsque l'utilisateur utilise l'astérisque ? 

I s'agit d'une des options suggérées dans le sujet, vous pouvez une fois que vous aurez terminé le corps obligatoire du projet vous attacher à l'implantation d'une des options suggérées mais dans l'attente il ne vous est pas demandé de le faire.

3) Je ne comprend pas l’intérêt de l'argument --print, car rsfind affiche les résultats quoi qu'il en soit non ? Même pour les fonctions find où ls je ne vois pas ce qu'apporte cette option. 

Non, si l'affichage n'est pas demandé il n'est pas demandé d'afficher, si aucune option particulière n'est précisée il faut considérer print comme option par défaut, autrement si jamais vous utilisez -l ou --exec il n'y a pas d'affichage à faire. Expérimentez dans votre terminal avec find, si vous utilisez -exec et pas -print vous n'aurez pas d'affichage des fichiers trouvés, à moins bien sûr que vous ne demandiez un echo {} dans le exec.

Le sujet précise une équivalence entre le rendu attendu et certaines commandes, par exemple "rsfind DOSSIER -l = find DOSSIER -exec ls -l {} \ ;"
Cette équivalence doit-elle être respectée au caractère près, ou doit-elle seulement renvoyer la même information ?
En d'autres termes, doit-on par exemple prendre en compte l'alignement de chacune des information, et donc adapter le nombre d'espaces à print (pour le nombre d'octets ou encore le mois de création par exemple), ou un décalage selon les ligne est accepté ?
Les tests automatiques réalisés pour noter le projet prendront-ils cela en compte ?

La réponse est oui, l'exactitude au caractère prêt est attendue dans les affichages. Je reconnais que dans le cas du ls -l ce sera fastidieux, moi-même j'y ai passé un certain temps mais ce genre de passages est inhérent à tout projet en informatique, vous y serez confrontés en entreprise alors autant commencer tout de suite. Je suis entièrement prêt à répondre à toute question relative à l'obtention des différentes informations affichées par la commande ls -l. Les documentations sont présentes sur internet mais vous gagnerez sans doute du temps en m'adressant vos questions même si la recherche de tutoriels adaptés est un très bon exercice pour votre pratique de développement.