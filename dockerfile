FROM alpine:latest

RUN apk add --no-cache gcc libc-dev make

COPY  vulnerable_program.c /vulnerable_program.c

RUN gcc -o /vulnerable_program /vulnerable_program.c

RUN adduser -D vulnuser

USER bulnuser

EXPOSE 8080

CMD ["/vulnerable_program"]

# docker build -t vuln-app .
# docker run -d -p 8080:8080 vuln-app

