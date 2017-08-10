# Using Tracer

Tracer supports tracing and vizualization for ROS nodes on a per process basis.

## 1. How to Install

```sh
$ cd $(TOPDIR)/Tracer
$ make
``` 

## 2. How to use

Please list the nodes you want to trace on the node_graph.yaml.
After that, please run Tracer, and GUI is launched.

Required ROS node information:

 * `nodename`: the name of ROS node
 * `sub_topic`: topic for subscribe (Not compulsory)
 * `pub_topic`: topic for publish  (Not compulsory)

## 3. If core dump occurs

Please comment out or uncomment `#DEFINE CORE_DUMP` in tracer.h.
