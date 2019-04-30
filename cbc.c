#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "tczero.h"
#include "cbc.h"

//-----------------------------------------------
void cbc_enc(uint64_t key[2], uint8_t *pt, uint8_t *ct, size_t ptlen){

    uint64_t* plaintext;    //Le plaintext découpé en part de 64bit
    uint64_t* cyphertext;   //Le cyphertext découpé en part de 64bit
    int i;
     
    //INITIALISATION 
    plaintext = (uint64_t*)pt; 
    cyphertext = (uint64_t*)ct; 

    uint64_t IV[2];    //Initialisation de IV, qui doit être random
    srand(key[0]); //On met à priori ce qu'on veut tant que ça part de la clef (genre key[0]&key[1] marche aussi)

	for(i=0; i<ptlen/64 ; i=i+2){
        
        if(i==0){
            //BLOC 1 : Plaintext XOR IV => cyphertext 
            IV[0] = rand();
            IV[1] = rand();
            cyphertext[0] = plaintext[0] ^ IV[0]; //cyphertext[0] = plaintext[0] XOR IV[0]
            cyphertext[1] = plaintext[1] ^ IV[1]; //cyphertext[1] = plaintext[1] XOR IV[1]
            tc0_encrypt(cyphertext, key);   //tc0_encrypt ne retourne rien, il modifie directement cyphertext
        }
        else{
            //BLOC i : Plaintext XOR cyphertext du bloc i-1 => cyphertext
            cyphertext[i] = plaintext[i] ^ cyphertext[i-2];
            cyphertext[i+1] = plaintext[i+1] ^ cyphertext[i-1];
            tc0_encrypt(cyphertext+i, key);

        }
        //printf("BLOC %d : %.8s%.8s = %llu%llu\n", i, (char*)(plaintext+i),(char*)(plaintext+i+1),(long long unsigned int)cyphertext[i],(long long unsigned int)cyphertext[i+1]);
	}
    printf("\n");
    
    
}
//-----------------------------------------------
//Permet de vérifier si le cryptage est déterministe : Si = 1, cbc_enc est déterministe, 0 sinon.
int test_cbc_enc_determinism(uint64_t key[2], uint8_t *pt, size_t ptlen){

	uint8_t *ct1; //premier cryptage de pt
	uint8_t *ct2; //deuxième cryptage de pt. Si ct1 = ct2, le cryptage est déterministe (et c'est mauvais !)

    ct1 = malloc(ptlen*sizeof(uint8_t));
	ct2 = malloc(ptlen*sizeof(uint8_t));

	cbc_enc(key, pt, ct1, ptlen);
	cbc_enc(key, pt, ct2, ptlen);

    int i;

	for(i=0; i<ptlen; i++){

		if(ct1[i] != ct2[i]){
			return 0;
		}
	}

	return 1;
}
//-----------------------------------------------
void cbc_dec(uint64_t key[2], uint8_t *ct, uint8_t *pt, size_t ctlen){

    uint64_t* cyphertext;   //Le cyphertext découpé en part de 64bit, contenant le message M' crypté
    uint64_t* plaintext;    //Le plaintext découpé en part de 64bit, vide pour l'instant
    int i;

    //INITIALISATION 
    cyphertext = (uint64_t*)ct; 
    plaintext = (uint64_t*)pt; 
    

    uint64_t IV[2];    //Initialisation de IV, qui doit être random
    srand(key[0]); 

	for(i=0; i<ctlen/64 ; i=i+2){

        if(i==0){
            //BLOC 1 : cyphertext => Plaintext XOR IV
            IV[0] = rand();
            IV[1] = rand();
            plaintext[0] = cyphertext[0];
            plaintext[1] = cyphertext[1];
            tc0_decrypt(plaintext, key); 
            plaintext[0] = plaintext[0] ^ IV[0]; // pour "annuler" le XOR
            plaintext[1] = plaintext[1] ^ IV[1];
        }
        else{
            //BLOC i : cyphertext => Plaintext XOR cyphertext du bloc i-1
            plaintext[i] = cyphertext[i];
            plaintext[i+1] = cyphertext[i+1];
            tc0_decrypt(plaintext+i, key);
            plaintext[i] = plaintext[i] ^ cyphertext[i-2];
            plaintext[i+1] = plaintext[i+1] ^ cyphertext[i-1];
        }
	}
}
//-----------------------------------------------

