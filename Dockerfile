# Base Debian avec GCC 11
FROM gcc:11-bullseye

RUN apt-get update
RUN apt-get install -y --no-install-recommends make valgrind openssl libssl-dev pkg-config

COPY src /app/src
COPY Makefile /app
COPY files /app/files

WORKDIR /app

RUN bash -c make compile

CMD ["bash"]