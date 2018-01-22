# C-ession-groupe3

Projet C pour le groupe 3 constitué de Chaka Ngameni, Romain Bozec, Vincent Romé, Julien Couillard

## Définition des termes

### Commandes envoyées par Central

GETCASE(x, y): Récupère la valeur d'une case.
SETCASE(x, y): Définit la valeur d'une case.
INSERERLIGNE(ligne): Insère une ligne.
SUPPRIMERLIGNE(x): Supprime une ligne.
CREERCOPIE(): Créé une copie de la liste chainée à un temps T.

### Structure de données

Liste chainée de T[Liste chainée à instant T, Liste chainée à instant T+1]
Liste chainée à instant T[index, tableau-contenant-la-ligne, référence-vers-ligne-suivante]

### Déroulement au lancement

#### Central

1. Recherche et lecture du fichier de conf
    * Fichier manquant, création d'un fichier par défaut et retour à 1
    * Fichier OK, mais impossible de se connecter à pair et/ou impair
        * Affichage d'un message: impossible de se connecter au module pair/impair, veuillez vérifier ...
        * Proposer de modifier la conf
    * Fichier OK, connexion OK, passer à 2.
1. Envoi d'une commande RESET() à PAIR et IMPAIR pour tout réinitialiser (ne pas oublier d'utiliser free() pour chaque élément de la liste).
1. RESET() terminé, on peut commencer, choix si on entre manuellement ou utilise un fichier.
1. Lecture des données d'entrée par Central et envoi des données ligne par ligne à Pair et Impair.
1. User entre les règles
    * Définir une couleur par règle
1. Choix entre défilement manuel ou auto pour un certain nombre de temps
1. Calcul des valeurs pour chaque T
    * Créer une copie de T
    * Modifier la copie
    * Stocker les modifs (fichier) et / ou les afficher.
1. Visualiser sur central (donc récup des données depuis Pair et Impair).

### Rôles

Romain: Structure de données
Jean : Configuration
Chaka : Visualiser
Julien : Lecture des règles
Vincent : Mise en réseau
