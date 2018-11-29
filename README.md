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

J'ai quelques questions à propos des tests blancs, je voudrais savoir :

- Si le test blanc va juger juste la partie du projet qui a été faite ou bien il va renvoyer des erreurs si toutes les étapes ne sont pas encore finies.

Oui, le test blanc va exécuter tous les items de la spécification qui vous a été fournie de sorte à vous fournir un point sur l'avancé de votre projet. Ce test vous permettra d'évaluer la note qui serait la votre si nous étions déjà à la fin du projet, je l'utiliserai encore pour la notation finale.

- Si le Makefile doit être fait et présent dans notre dépôt.

Oui, la première étape du test blanc consistera à lancer la compilation de votre projet via le Makefile, si cette étape ne fonctionne pas alors tout le reste sera caduc et votre projet sera évalué en conséquence, veillez donc bien à avoir un Makefile opérationnel dans votre dépôt.

- Si on doit avoir sur notre dépôt que la dernière version de notre fichier rsfind

C'est nativement pris en compte par git, si votre Makefile est bien conçu il ne devrait pas y avoir de problème, veillez simplement bien à ce que le nom de votre exécutable soit rsfind.

    Nous avons du mal à comprendre la syntaxe demandée pour les pipes du --exec, faut il que l'utilisateur écrire des pipes sous la formes de plusieurs commandes : ./rsfind --exec "CMD1" "CMD2" ./          (Pour pipe CMD1 sur CMD2)
ou : ./rsfind --exec "CMD1 | CMD2" ./

La syntaxe attendue est rsfind . --exec "cat {} | cat | cat".

Les fonctions de type exec sont autorisées pour l'implémentation de la commande 'exec' de rsfind, mais est-il autorisé de faire quelque chose du genre execlp("sh","sh","-c",command,NULL) ?

Non, il est attendu que vous implantiez par vous-mêmes les spécifications du projet, en somme pour toute fonctionnalité autre que l'option --exec l'utilisation des fonctions de la famille exec est strictement interdite, il serait autrement trop simple de se cantonner à faire un "bête" copié collé des commandes de l'énoncé dans des exec ajustés de sorte à avoir le résultat attendu.

L'équivalence "rsfind DOSSIER -l = find DOSSIER -exec ls -l {} \;" est un peu étrange puisque ls s'exécute aussi sur les dossiers que trouve find.

Oui, il s'agit en effet d'une coquille du sujet, il faut prendre en compte l'équivalence avec find DOSSIER -exec ls -l -d {} \;, l'option -d permet en effet de bloquer le détail du contenu des répertoires.

d'après le sujet il est possible de combiner l'option -t et l'option -i. Cela nous semble cependant étonnant de rechercher un champs texte dans un fichier image. Pouvez-vous, s'il vous plaît, nous confirmer que l'on aimerait vraiment combiner ces deux options ?

En effet il vous est demandé de soutenir la combinaison d'options, -t, -i et --name peuvent être utilisées simultanément dans une recherche de fichiers, -i et -t renverra les fichiers images contenant une certaine chaîne, -i et --name les fichiers images d'un certain nom et -t et --name les fichiers d'un certain nom contenant une certaine chaîne.

Nous pensions aussi à d'autres combinaisons possibles avec exec : est-ce que exec est combinable avec --name ou -t ou encore -i ?

En effet, les commandes --exec, --print et -l peuvent elles aussi être combinées. La première série d'options (-i, -t et --name) définissent des critères sur la recherche de fichiers, les trois autres options des modes d'affichages différents. Dans le cas où vous demandez plusieurs affichages il faut faire un affichage dans l'ordre print / listing / exec si je ne m'abuse mais il faudrait relire le sujet qui vous informera à ce propos.

Je souhaiterais m’intéresser au fichier YML, vous aviez parlé d'un fichier : .gitlab-ci.yml, je voudrais le réaliser car ses apports pourraient être intéressant pour notre projet et la réalisation d'une batterie de test exécuté à chaque push pourrait être une bonne compétences à acquérir.

Très bonne initiative, je félicite encore le(s) groupe(s) concerné(s) pour cette marque d'investissement et de professionnalisme. Voici ci-dessous un lien qui permettra à tous les élèves intéressés d'en faire de même, la présence d'un tel fichier de tests sera prise en compte lors de l'évaluation finale comme marque d'un investissement particulier dans la mise en place d'une politique de tests rigoureuse :

https://docs.gitlab.com/ee/ci/yaml/

Je tente de développer les extensions pour le projet de RS.
J'ai une question à propos de l'extension --ename:
Est-ce une expression régulière qu'il faut passer en paramètre ou une expression composée de métacaractère shell ?
Par exemple, faut-il passer:
.*.txt pour obtenir les fichiers avec pour extension txt ou bien *.txt comme pour find?
Si c'est la deuxième solution, faut-il toujours utiliser la bibliothèque libpcre ?
Si c'est bien le cas, je n'ai pas trouvé, malgré mes recherches, la manière de configurer pcre pour détecter les métacaractères shell au lieu des expressions régulières "classiques".

L'option --ename accepte bien une expression contenant des méta-caractères shell. Je n'ai pas trouvé moi non plus de solution simple pour parser ce genre d'expressions, je pense que le mieux est de faire une sorte d'association entre les méta-caractères shell et des expressions régulières équivalentes (ex. * -> .*).