#!/bin/sh

echo 0 > /sys/kernel/debug/tracing/tracing_on
echo 0 > /sys/kernel/debug/tracing/events/enable
cat /sys/kernel/debug/tracing/trace > trace.log
cat /sys/kernel/debug/tracing/trace_pipe > trace_pipe.log

umount /sys/kernel/debug/
