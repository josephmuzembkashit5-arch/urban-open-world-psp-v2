# Urban Open World PSP — Prototype 0.1

Prototype original de jeu 3D pour PSP / PPSSPP, conçu comme base technique pour un monde ouvert.
Il ne contient aucun fichier, personnage, mission ou ressource de GTA V.

## Compilation sur GitHub Actions

1. Crée un dépôt GitHub vide avec la branche `main`.
2. Téléverse le contenu de cette archive à la racine du dépôt, y compris `.github/workflows/build.yml`.
3. Ouvre **Actions** et sélectionne **Build PSP prototype**.
4. Si GitHub demande d'autoriser les workflows, accepte.
5. Après une compilation réussie, télécharge l'artefact `urban-open-world-psp-build`.

L'artefact doit contenir `EBOOT.PBP`. La compilation en ligne ne remplace pas un test dans PPSSPP.

## Prototype inclus

- Scène 3D simple : sol et personnage géométrique.
- Contrôle du personnage avec le stick analogique.
- Rotation de caméra avec gauche/droite sur la croix directionnelle.
- Pas de modèles externes requis.

Le rendu est volontairement simple pour établir une base stable avant d'ajouter des éléments plus lourds.
