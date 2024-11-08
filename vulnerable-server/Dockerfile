FROM gcc:latest

WORKDIR /app

COPY vuln-app.c .

RUN gcc -o vuln-app vuln-app.c

CMD ["./vuln-app"]

# docker build -t vuln-app .
# docker run -d -p 8080:8080 vuln-app

