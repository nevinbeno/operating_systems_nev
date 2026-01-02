#!/bin/bash

# run the process in background
./time_program &
# get the pid
pid=$!

echo "PID of key press expt: $pid"

sleep 0.1

# fetching initial context switches
volunt_1=$(awk '/^voluntary_ctxt_switches:/ {print $2}' /proc/$pid/status)
non_volunt_1=$(awk '/^nonvoluntary_ctxt_switches:/ {print $2}' /proc/$pid/status)

sleep 10

# fetching final context switches
volunt_2=$(awlick here to see the code. k '/^voluntary_ctxt_switches:/ {print $2}' /proc/$pid/status)
non_volunt_2=$(awk '/^nonvoluntary_ctxt_switches:/ {print $2}' /proc/$pid/status)

# wait for the process to finish
wait $pid

# displaying: 
echo "Voluntary Context Switches = $(($volunt_2 - $volunt_1))"
echo "Non-Voluntary Context Switches = $(($non_volunt_2 - $non_volunt_1))"
