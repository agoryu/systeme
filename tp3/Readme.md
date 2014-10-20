Ordonnancement sur interruptions
================================

# Auteur

- Elliot Vanegue
- Gaetan Deflandre


# Description

Le programme change de contexte avec un ordonnancement sur interruption.

Dans notre exemple, le programme ne boucle plus à l'infini, mais se 
termine sur le main. Nous conservons les registres *esp* et *ebp*, 
lors du premierappel à *switch\_to\_ctx*.

Pour illustrer les interruptions, nous avons utilisés la fonction sleep.
Ce qui laisse le temps au programme de changer de contexte.

## Output:

	$ Aa1Bb2Cc3

Le programme passe bien de fonction en fonction pendant leurs 
execution.

