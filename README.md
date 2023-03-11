## Example of protocols

## Usage

### udb4 server

```bash
make udb4Server PORT=1234
```

### udb6 client

```bash
make udb6Server PORT=1234
```

you can then communicate with the server using for example netcat:

```bash
nc -u 127.0.0.1 1234
RANDOM DATA
```

and it will be printed on the server side