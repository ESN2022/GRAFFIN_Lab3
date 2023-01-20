# GRAFFIN_Lab3


## Introduction


Dans ce dernier Lab, je vais mettre en œuvre un flow de conception codesign dans un exemple plus complexe: l'interfassage de l'acceleromètre ADXL345. Pour cela, je vais utiliser la carte de développement DE10 Lite avec son FPGA. Je vais aussi utiliser la suite d'intel : Quartus 18.1 avec Platform Designer.
Le but est ainsi de communiquer en I2C avec l'acceléromètre et d'afficher la valeur de l'accélération en g sur les afficheur 7 segments, présents aussi sur la carte de développement DE10 Lite. Je vais aussi utiliser un boutons de cette carte pour ajouter certaines fonctionnalités.


## Architecture


Pour cet exercice, j'ai utilisé un Nios2 avec ses périphériques nécessaire pour qu'il fonctionne et le debugguer : Mémoire RAM, JTAG debugger, Clock. Pour interfacer tous les autres périphériques (bouton, afficheur) j'ai utilisé des PIO. Le tout communiquant avec le bus Avalon. Le montage final sur Platform Designer se trouve sur l'image ci-dessous avec le schéma:



J'ai utilisé 3 PIO pour connecter les périphériques extérieurs au FPGA, car les LEDs sont en sortie alors que les boutons et les switchs en entrée et j'ai différencié les switchs aux boutons pour que ce soit plus pratique dans le code C.
De plus, mon bloque hardware est simple, c'est juste la connexion avec la clock, le reset et les PIO dans le VHDL, et grâce à la datasheet de la carte DE10 Lite, j'ai connecté dans le pin planer les bonnes Pin avec mes ressources.


## Results / Progress

Le premier résultat, allumer un led était simple, sans trop de problèmes et surtout avec un code C minime. La prochaine étape était de faire le chenillard en lui même, encore une fois pas très compliqué. Là où j'ai eu plus de mal, c'est lorsqu'il a fallu changer la manière d'interagir avec le bouton et les switchs. En effet, les interruptions pour gérer la vitesse et le bouton start n'ont pas été simple à mettre en oeuvre.
Finalement, j'ai réussi à aller au bout de ce lab avec un chenillard sur les Leds qui est déclenché par un bouton géré par une interruption et dont la vitesse peut être changée via les switchs, eux même gérés avec une interruption. 

## conclusion

Ce lab m'a permis d'appréhender  un peut mieux le flow de conception en co-design, avec les commandes, l'ordre des manipulations, l'interaction entre le hard et le soft ou le pin mapping. Il y a certaines étapes que je n'avais jamais fait et cela m'a permis d'être sur de les comprendre pour pouvoir les reproduires lors des prochains lab et plus tard encore.
Le seul point noir où j'ai eu du mal a été par rapport aux interruptions que j'ai solutionné grâce à la documentationet à mes collègues.

