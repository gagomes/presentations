pmls (aka poor man's logstash)

A simple pipeline, that could replace 'cp'. It's mostly an exercise in 
displaying the use of plugins, in which one could define a plugin such 
as stdin.so to read from anything (hdfs, kettle meter) and have an output
plugin which would take that information and write it elsewhere, in an 
arbitrary format. 

Usage

```shell
# find / | ./pmls stdin.so stdout.so  > foo
Processed 20764312 bytes
```
