# Partie appolab

## Note (grosse erreur de ma part)

Pensant que cette partie du code n'était pas à rendre comme il s'agissait d'un bonus, j'ai programmé mon programme de résolution en Rust avec un client AppoLab en Rust programmé il y a un mois pour m'exercer (https://github.com/edgarogh/appolab/). Je m'en suis rendu compte trop tard qu'il fallait également rendre ce code et n'ai pas le temps de tout traduire en C. Le Rust comme le C sont des langages de bas niveau mais Rust possède des abstractions très nombreuses et des structures de contrôle spécifiques aux langages fonctionnels qui rendent le code difficile à réécrire (ou même transpiler automatiquement).

J'imagine que le rendu de code a surtout pour but d'éviter le plagiat, donc je me permet de l'inclure quand même dans le projet, au cas où il est possible d'en tirer une fraction de points.

## ents

_c.f. `src/ents.rs`_

Seule la partie "ents" a été réussie.

Compilation + Execution (il faut donc la toolchain Rust https://rustup.rs/):
```
# Remplacer les identifiants AppoLab
APPOLAB_CREDS="123456789 NOMDEFAMILLE" cargo run
```

## hero

_c.f. `src/hero.rs`_

Cette partie n'a pas réussi mais j'ai beaucoup progressé (jusqu'à être bloqué par une boucle, que je détecte, mais quand je la filtre, il ne me reste plus aucun chemin à essayer).
