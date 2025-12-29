#!/bin/bash

# Run the program in background
./time_program &
pid=$!
echo "PID of time_program: $pid"

# Wait a second to ensure /proc/[PID]/stat exists
sleep 1

# Extract utime and stime in seconds using awk
awk -v pid=$pid '
{
    utime = $14
    stime = $15
    clk = 100  # clock ticks per second
    printf "User mode time: %.3f seconds\n", utime/clk
    printf "Kernel mode time: %.3f seconds\n", stime/clk
}
' /proc/$pid/stat
