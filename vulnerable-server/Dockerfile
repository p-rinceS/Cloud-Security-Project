FROM debian:bullseye

WORKDIR /usr/src/app

COPY . .

# Add i386 architecture and update package lists
RUN dpkg --add-architecture i386 && \
    apt-get update && \
    apt-get install --assume-yes --no-install-recommends --quiet \
    build-essential \
    gcc-multilib \
    g++-multilib \
    autoconf \
    automake \
    libtool \
    net-tools \
    openssh-server \
    libc6:i386 \
    libc6-dev:i386 \
    libgcc1:i386 \
    libstdc++6:i386 \
    libgcc-s1:i386 \
    lib32gcc-10-dev \
    lib32stdc++6 \
    netcat \
    python3 \
    zsh

# Create SSH directory and set root password
RUN mkdir /var/run/sshd
RUN useradd -m user
RUN echo 'user:password' | chpasswd
RUN echo 'root:password' | chpasswd

# Configure SSH server
RUN sed -i 's/#PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config

# Expose ports
EXPOSE 22
EXPOSE 9090

# Compile the threaded_serv.c
RUN gcc -fno-stack-protector -z noexecstack -o threaded_serv threaded_serv.c -lpthread

# Compile retlib.c as a 32-bit executable
RUN gcc -m32 -fno-stack-protector -z noexecstack -o retlib retlib.c -lpthread

#compile printenv.c
RUN gcc -m32 -o printenv  printenv.c

# Set permissions for the executables
RUN export MYSHELL=/bin/bash
RUN export MYFLAG=-p
RUN chown root threaded_serv
RUN chmod 4755 threaded_serv
RUN chown root retlib
RUN chmod 4755 retlib
RUN chown user printenv
RUN chmod 777 printenv
RUN apt-get update && apt-get install -y openssh-server
RUN apt-get install -y curl
RUN chsh -s $(which zsh)
RUN ln -sf /bin/zsh /bin/sh

# Start SSH service and run both programs
CMD service ssh start && ./threaded_serv
