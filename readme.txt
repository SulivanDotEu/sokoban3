BOUTONS GRAPHIQUES

De gauche à droite:

- sauvegarde de l'etat du jeu
- chargement de l'etat du jeu contenu dans la sauvegarde
- rechargement du jeu en cours (jeu peut etre considere comme niveau, ou map)
- chargement du prochain jeu (jeu peut etre considere comme niveau, ou map)
- avancer a gauche
- avancer en bas
- avancer a droite
- avancer en haut

BOUTONS

A) DEZOOM
Z) ZOOM
U) UNDO
FLECHE_GAUCHE) avancer a gauche	
FLECHE_BAS) avancer en bas
FLECHE_DROITE) avancer a droite
FLECHE_HAUT) avancer en haut

Remarque :

Quand le jeu se lance, le fichier levels.txt (par defaut) se charge. Ce fichier contient la liste (dans l'ordre) des niveaux du jeux.
La sauvegarde retient l'etat du niveau actuel mais aussi elle retient la position dans la liste des niveaux (et le nom du fichier qui contient cette liste).

GRAPHES DE SCENES

MyView (View.h) contient 2 cameras:
	- celle de la gameView
	- celle du controlView
		
GameView contient une camera qui elle meme contient:
	- une collection de Platforms et d'ObjectView (joueur, mur, etc...).
	
Ces objets contiennent CHACUN un "pat" : PositionAttitudeTransform
	Celui ci contient indirectement une forme, par l'intermediaire d'une geode.
	Cette geode est commune à tout les objets du même type.
		A savoir tout les murs possedes la même geode, et donc la meme forme.
		nb : chaque murs possedent leur propre pat.

OBJET GRAPHIQUE

Le joueur, represente graphiquement par la classe PlayerView, repond aux exigences suivantes:
Au moins un des objets graphiques devra être entierement defini dans le code en 
termes de primitives graphiques, cette definition incluant la ou les couleurs ainsi 
que les vecteurs normaux ; 

Tout les autres elements graphiques repondent aux exigences suivantes:
Au moins un des objets graphiques devra utiliser une texture pour son apparence 
finale. 

Diagramme de classe :
	
	Pour les elements du jeu on distingue deux types : Case et Casecontents.

	CaseContents a plusieurs sous-types : MyBox, Player et Wall. La logique de deplacement est defini dans chaque CaseContents, ceci dans le but de pouvoir rajouter aisement
	de elements bougeant de façon differentes.

	Une Case peut soit être vide, soit contenir un CaseContents. Une case peut aussi être un socle ou non.
	
	Chaque vue a sa propre classe.

	En ce qui concerne le pattern command :
		
		Chaque commande concrete implemente l'interface Command.

