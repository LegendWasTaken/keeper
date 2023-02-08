# Keeper 
A highly configurable server for hosting resources for portfolio websites

# Motivation 
On the 4th rewrite of my own website, I realized that the main thing that was always a roadblock was a backend. So I had the bright idea to write a backend myself, then I rewrote it... then I rewrote it again. With every iteration, I realized I had more and more requirements. But, they were all somewhat similar. So I had the "brilliant" idea of asking. What if I just wrote a single project that was general purpose enough to handle everything I might need?

Now we're here, with a brand spanking new git repository and a dream.

# Usage
1) Compile the project on your machine // Todo - Link to compile instructions 
2) Create a folder called `keeper` wherever you see fit. (The program will only use this directory)
3) Run 
```shell
$ ./keeper --init --path=<path/keeper>
```
(Generates all the basic configurations)
4) Optionally, run
```shell
./sudo keeper --write-service --path=<path/keeper>
```
(Generates a service file in the PWD)
5) Setup the configuration files to your requirements, run and (hopefully) enjoy

# Config
There are a few types of configurations, I'll run down the different types here in the beginning so you know what to look for

Note: All configuration files (unless stated otherwise, are `.toml` files)

`server.config`: Used for the http server / config side of things

`log.config`: Used for logging (types of levels to use, sinks, etc...)

`resources.config`: Used for defining the resources that the server will serve 

## Sample configurations 
(Note: Potentially not exhaustive of all options, for a list of all options look [here]) - Todo: Link

`server.config`
```toml
ip = "192.168.0.1" # IP that server will bind to
port = "25565" # Port server will bind to
timeout = 5000 # Timeout in milliseconds 

[threads]
queue = 4 # Number of threads used for processing resource requests
request = 8 # Number of threads used for handling http requests 

[responses]
not_found = "./respond/404.json"
success = "./respond/found.json"
timeout = "./respond/timeout.json"
```

`log.config`
```toml
[sinks.error] # Keep errors in their own file 
type = "file"
levels = ["error"] # Only output errors
file = "log/error.log"

[sinks.all] # Catch all (important to production) logs
type = "file"
levels = ["error", "warn", "info"]
file = "log/all.log"

[sinks.console] # Could be used in a development enviroment / staging
type = "console"
levels = ["error", "warn", "info", "debug"]
```

`resources.config`
```toml
[storage.clickhouse]
type = "clickhouse" # View all storage types [here] - todo...
database_name = "keeper" # In clickhouse, a table will be generated for this 
address = "127.0.0.1" # Clickhouse server address
port = "12345" # Clickhouse server port
username = "foo" # Clickhouse database username
password = "bar" # Clickhouse database password

[types.blog.fields]
title = "string" # utf8 string
description = "string"
content = "string"
upload = "timestamp" # unix 64 bit timestamp
edited = "timestamp"
authors = "string[]" # array of utf8 strings
image = "webp" # a .webp image, specific storage requirement varies between storage types
impressions = "u64"

[types.blog.abilities.request_count]
enable = true
associate_with = "impressions" # Must be a u64 type
```
