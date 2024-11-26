FROM i386/gcc:latest

WORKDIR /usr/src/app

COPY . .

# Install necessary packages
RUN apt-get update && apt-get install -y \
    net-tools \
    openssh-server

# Create SSH directory and set root password
RUN mkdir /var/run/sshd
RUN useradd -m user
RUN echo 'user:password' | chpasswd

# Configure SSH server
RUN sed -i 's/#PermitRootLogin prohibit-password/PermitRootLogin yes/' /etc/ssh/sshd_config

# Expose ports
EXPOSE 22
EXPOSE 9090

# Compile the threaded_serv.c
RUN gcc -fno-stack-protector -z noexecstack -o threaded_serv threaded_serv.c -lpthread
RUN gcc -m32 -fno-stack-protector -z noexecstack -o retlib retlib.c -lpthread
RUN chown root threaded_serv
RUN chmod 4755 threaded_serv
RUN chown root retlib
RUN chmod 4755 retlib

# Start SSH service and threaded server
CMD service ssh start && ./threaded_serv