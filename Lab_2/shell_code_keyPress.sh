#!/bin/bash

# run the process in background
./key_press &
# get the pid
pid=$!

echo "PID of key press expt: $pid"

sleep 0.1

# fetching initial context switches
volunt_1=$(awk '/^voluntary_ctxt_switches:/ {print $2}' /proc/$pid/status)
sleep 5
# fetching final context switches
volunt_2=$(awk '/^voluntary_ctxt_switches:/ {print $2}' /proc/$pid/status)

# wait for the process to finish
wait $pid

# displaying: 
echo "Voluntary Context Switches = $(($volunt_2 - $volunt_1))"
