# Créer un container docker
```shell
# Build
sudo docker build -t mehdi_mascret_mssis .
# Lancer le container
sudo docker run --rm -it mehdi_mascret_mssis bash
```
# Tester le logiciel
```shell
# Compiler d'abord et toujours le code !
make compile
# Lancer le mode Generate
./target/src/main -G files/rockyou.txt files/keyvalue.txt
# Penser à bien faire cette commande pour voir les hash histoire de ne pas tester sans avoir de hash en tete
cat files/keyvalue.txt | head -n 100
# Lancer le mode Load
./target/src/main -L files/keyvalue.txt

```
## Valgrind
Mon code se lance en moin de 10 secondes mais valgrind prend 1 minutes, ce qui est très inconfortable !
```shell
# Mode Generate
valgrind target/src/main -G files/rockyou.txt files/keyvalue.txt
# Mode Load
valgrind target/src/main -L files/keyvalue.txt
```
## Autre mode de hashage pour le mode generate
```shell
# Par défaut c'est l'algo 512
./target/src/main -G files/rockyou.txt files/keyvalue.txt -Algo SHA512
# Algo 256
./target/src/main -G files/rockyou.txt files/keyvalue.txt -Algo SHA256
```