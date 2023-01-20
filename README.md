# GRAFFIN_Lab3


## Introduction


Dans ce dernier Lab, je vais mettre en œuvre un flow de conception codesign dans un exemple plus complexe: l'interfassage de l'acceleromètre ADXL345. Pour cela, je vais utiliser la carte de développement DE10 Lite avec son FPGA. Je vais aussi utiliser la suite d'intel : Quartus 18.1 avec Platform Designer.
Le but est ainsi de communiquer en I2C avec l'acceléromètre et d'afficher la valeur de l'accélération en g sur les afficheur 7 segments, présents aussi sur la carte de développement DE10 Lite. Je vais aussi utiliser un boutons de cette carte pour ajouter certaines fonctionnalités.


## Architecture


Pour cet exercice, j'ai utilisé un Nios2 avec ses périphériques nécessaire pour qu'il fonctionne et le debugguer : Mémoire RAM, JTAG debugger, Clock. Pour interfacer tous les autres périphériques (bouton, afficheur) j'ai utilisé des PIO. Il y a aussi un timer pour cadencer les mesures et l'affichage à 1Hz. Le tout communique avec un bus Avalon. Le montage final sur Platform Designer se trouve sur l'image ci-dessous avec le schéma:

![Sans titre](https://user-images.githubusercontent.com/75631006/213670692-9f16a47c-aa75-4828-adeb-736cc73c5b3c.png)

![image](https://user-images.githubusercontent.com/75631006/213668829-f03b643f-af11-4d09-b088-4f8d300b0dc8.png)

J'ai utilisé 1 PIO pour connecter les afficheurs 7 segments, car ils ont la même direction et qu'ils sont lié en terme de pilotage dans le code en C. Pour utiliser les afficheurs, j'ai instencié 2 bloc hardware qui se ressemble beaucoup et qui permettent de convertir les données qui arrive de la PIO en binaire en un signal correct pour un afficheurs 7 segments. La seule différence est que l'un active le point et l'autre non.


## Results / Progress

Le premier résultat, comminiquer avec l'accéléromètre, était une partie critique et était assez complexe à réaliser. La lecture de la doc était obligatoire pour comprendre et arrivé au but de l'étape. 
La calibration du capteur a été rapide car il ne driftait presque pas, c'est pourquoi il n'y a pas eu d'offset de mis.
Les étapes suivantes, l'affichage sur des afficheurs 7 segments et le réglage de l'axe avec un bouton ont était réalisé grâce à ce que j'avais déjà réalisé lors des précedents Lab, donc sans trop de problème. Le Timer et le bouton sont gérés par interruption. On obtient finalement le résultat dans les vidéos suivantes, avec un système qui est calibré et qui respecte le cahier des charges.

https://user-images.githubusercontent.com/75631006/213673291-1132d943-623e-49fe-9183-3a090a02e856.mp4

https://user-images.githubusercontent.com/75631006/213673690-46928d32-a5f8-43c9-b3ad-18593be0ba1f.mp4


## conclusion

Ce lab m'a permis d'appuyer mes connaissances en codigne que j'avais appr_s au cours des deux premier Lab. En effet, j'ai réutiliser ce que j'avais déjà fait, notament avec l'afficheur, le timer et le bouton. Ainsi, le seul point bloquant de ce Lab était la communication I2C avec l'accéléromètre, que j'ai fini par réussir.

