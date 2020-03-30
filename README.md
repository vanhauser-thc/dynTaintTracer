# dynTaintTracer

a tain tracer based on DynamoRIO, currently ARM only (but might already work
with AARCH64 too).
I wrote this in Summer 2018 for a few automotive pentest/reversing projects,
but what the heck, lets release this to the world as others might find it
useful too.

Note the AGPL3 license.

## Building dynTaintTracer

1. set the environment variable `DYNAMORIO_HOME` to the build directory of DynamoRIO.
2. type `make` and `sudo make install`

*You must compile on ARM (not Intel!)*
(and might work on AARCH64)

## Running

Use the helper script `dynTaintTracer.sh`.
The following options are supported:
```
--taint-accept	 taint accept() and recvfrom()
--taint-connect	 taint connect() sendto()
--taint-sslread	 taint SSL_read()
--taint-stdin	 taint stdin
--taint-file     taint reads from this file
--workaround	 work around a bug in dynamorio concerning strex
--report-debug	 debug output
--report-unknown report unknown instructions
--report-problem report problems
--report-untaint report untainting instructions
--trace-inst	 report all instructions when there is taint
--trace-bb	 report all basic blocks when there is taint
--trace-indirect report all indirect call/jmp when there is taint
--outfile	 where to write the trace output to
```
e.g.
```
# dynTaintTracer.sh --taint-file /tmp/foo.txt --outfile /tmp/trace.log --report-untaint -- /target/program -f /tmp/foo.txt
```

## And then?

You can load the results into IDA with the included IDC script `dynTaintTracer.idc`.
Just run the script which opens a file select window, select the trace and it
is then applied to the loaded binary.

## Caveats

Works fine, but neon instructions are not supported currently.

## Future

It is easy to expand to AMD64, i686, etc. - "just" the instructions
have to be added to `ops_intel.c` and for AARCH64 to `ops_aarch.c`.
