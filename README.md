## Example of protocols

## Usage

### udb4 server

```bash
make udb4Server PORT=1234

```

### udb6 server

```bash
make udb6Server PORT=1234
```

you can then communicate with the server using for example netcat:

```bash
nc -u 127.0.0.1 1234
RANDOM DATA
```

### tcp4 server with thread pool

```bash
make tcp4ServerWithThreads PORT=1234 MAX_CONNECTIONS=2
```

you can then communicate with the server using for example netcat:

```bash
nc 127.0.0.1 1234
RANDOM DATA
```
it will print tcp handshake and acknowledge the data

and it will be printed on the server side

### http 1.1 server

```bash
make httpServer PORT=1234 MAX_CONNECTIONS=4
```

you can then communicate with the server using for example curl:

```bash
curl 127.0.0.1:1234 -v
```