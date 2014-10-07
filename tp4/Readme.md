Coroutine
=========

# Auteur

- Elliot Vanegue
- Gaetan Deflandre


# Description

La fonction *switch\_to\_ctx* permet d'échanger des contextes. Cela signifie
que la méthode va passer d'une pile à une autre lors de l'exécution. Une 
pile distincte pour ping, pong et pang.

Le programme ne boucle plus à l'infini, mais se termine sur le main. Pour
cela, nous avons conservé les registres *esp* et *ebp*, lors du premier
appel à *switch\_to\_ctx* dans des variables globales.

