# ft_traceroute

This project is a custom implementation of the `traceroute` utility, a network diagnostic tool used to track the path that packets take from your machine to a specified destination host. It works by sending packets with increasing Time-To-Live (TTL) values and analyzing the ICMP responses received from each hop along the route.

## Options

| Short opt | Long opt            | Description                                    |
|:---------:|---------------------|------------------------------------------------|
| `-f`      | `--first-hop=NUM`   | Set initial hop distance, i.e., time-to-live   |
| `-m`      | `--max-hops=NUM`    | Set maximal hop count (default: 64)            |
| `-p`      | `--port=PORT`       | Use destination PORT port (default: 33434)     |
| `-q`      | `--tries=NUM`       | Send NUM probe packets per hop (default: 3)    |
| `-w`      | `--wait=NUM`        | Wait NUM seconds for response (default: 3)     |
| `-?`      | `--help`            | Give this help list                            |
|           | `--usage`           | Give a short usage message                     |


## Build Instructions
To build the ft_traceroute executable, use make:

```
make
```

## Examples

Traceroute with a custom initial TTL:

```
./ft_traceroute -f 5 google.com
```

Traceroute with a custom timeout:

```
./ft_traceroute -w 2 google.com
```
