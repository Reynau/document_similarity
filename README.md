# Document Similarity detection with Hashing

L’objectiu d’aquesta pràctica és per una part analitzar l’efectivitat de la detecció de similitud de
documents de text en funció de la precisió de la representació del text i per una altra, implementar
un algorisme de detecció de documents similars basats en hash. Per això us proposem que considereu
representacions dels documents basades en l’us de k-shingles (o k-grams) i de signatures minhash
per tal d’avaluar l’efectivitat de la mesura de similitud computada. Una vegada determinats els
paràmetres adients per a una col·lecció, volem un algorisme per determinar els documents mes
similars d’un donat.

## Objectives

- Obtain **Jaccard** similitude index for documents represented with **k-shingle**.
- Obtain **Jaccard** similitude index for documents represented with **minhash**.
- Implement a **Locality-Sensitive Hashing (LSH)** algorithm based on **minhash**.
