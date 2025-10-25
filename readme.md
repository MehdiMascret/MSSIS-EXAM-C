# Tester le logiciel
```shell
# Compiler d'abord et toujours le code !
make compile
# Lancer le mode Generate
./target/src/main -G files/rockyou.txt files/keyvalue.txt
# Lancer le mode Load
./target/src/main -L files/keyvalue.txt[main.c](src/main.c)

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
