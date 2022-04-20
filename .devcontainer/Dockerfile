FROM    debian:latest

RUN apt-get update \
 && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    'build-essential' \
    "valgrind" \
    "gdb" \
    'automake' \
    'make' \
    'ca-certificates' \
    'g++' \
    'libtool' \
    'pkg-config' \ 
    'manpages-dev' \
    'zip' \
    'unzip' \
    'python3' \
    'python3-pip' \
    'git' \
    'openssh-server' \
    'dialog' \
    'llvm' \
    'zsh' \
    'wget' \
    'clang' \
    'nano'  \
    'zlib1g-dev'    \
    'libxext-dev'   \
    'libx11-dev'    \
    'libbsd-dev' \
    'libreadline-dev' \
    'lldb'      \
    xorg    \
    && apt-get clean autoclean \
    && apt-get autoremove --yes \
    && rm -rf /var/lib/{apt,dpkg,cache,log}/

RUN python3 -m pip install --upgrade pip setuptools
RUN python3 -m pip install norminette


RUN sh -c "$(wget -O- https://github.com/deluan/zsh-in-docker/releases/download/v1.1.2/zsh-in-docker.sh)" -- \
    -t robbyrussell \
    -p git 


WORKDIR /app

COPY ../ .