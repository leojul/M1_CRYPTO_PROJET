# Projet Cryptologie

## Cryptage

![alt text](https://upload.wikimedia.org/wikipedia/commons/thumb/8/80/CBC_encryption.svg/601px-CBC_encryption.svg.png "Cryptage par CBC")

Soit un message M que nous souhaitons crypter, morceau par morceau. Ce message M, codé sur x bits sera divisé en plusieurs bouts (les plaintext) de 64 bits (le dernier plaintext à traiter contiendra les bits restants.) Pour chaque bloc de chiffrement (fourni dans tczero.h), on donne en paramètre des entrées de 64 bits : 
- Un plaintext qui aura subit au préalable un XOR avec un vecteur de 64 bits aussi. Ce vecteur sera IV pour le premier bloc, et le cyphertext
- La clef
Elle donnera en sortie un cyphertext, le plaintext chiffré. Pour chaque bloc i, on donne le plaintext i, qui, une fois tous chiffrés, donnera le message complet M', chiffré. On remarquera que le plaintext subit au préalable un XOR avec un vecteur de 64 bits aussi. Ce vecteur sera IV (généré aléatoirement) pour le premier bloc, et le cyphertext du bloc d'avant pour les autres blocs.


## Décryptage

![alt text](https://upload.wikimedia.org/wikipedia/commons/thumb/2/2a/CBC_decryption.svg/601px-CBC_decryption.svg.png "Cryptage par CBC")

Là encore, pas plus compliqué que le cryptage : Le message chiffré M' est divisé en part de 64 bits. Chaque part est donnée en entrée (avec la clef) au bloc de chiffrement de décryptage. De ce bloc en ressort :
- le (plaintext XOR IV) dans le cas du premier bloc.
- le (plaintext XOR le cyphertext du bloc d'avant) dans le cas des autres blocs.

Pour retrouver le premier plaintext, il nous faut IV, (déduit de la clef). Cependant, cela rend le cryptage déterministe.




