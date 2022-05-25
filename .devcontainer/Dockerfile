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
    -p git \
    -p gh

RUN curl -fsSL https://cli.github.com/packages/githubcli-archive-keyring.gpg | dd of=/usr/share/keyrings/githubcli-archive-keyring.gpg
RUN echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/githubcli-archive-keyring.gpg] https://cli.github.com/packages stable main" | tee /etc/apt/sources.list.d/github-cli.list > /dev/null
RUN apt update
RUN apt install gh

ENV USER=Dokcer
ENV HOSTNAME=42MINISHELL

COPY ../ .