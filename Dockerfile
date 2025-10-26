# Base Debian avec GCC 11
FROM gcc:11-bullseye

RUN apt-get update
RUN apt-get install -y --no-install-recommends make valgrind openssl libssl-dev pkg-config

COPY src /app/src
COPY Makefile /app
COPY files /app/files

WORKDIR /app

CMD ["bash"]

RUN make compile

#Génère la rainbow table pour plus de confort lors des testes
RUN target/src/main -G files/rockyou.txt files/keyvalue.txt

