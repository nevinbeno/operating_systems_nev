#!/bin/bash

total_logical_cpu_sores=$(grep -c "processor" /proc/cpuinfo)

total_memory=$(grep "^MemTotal" /proc/meminfo | awk '{print $2}')
total_free_memory=$(grep "^MemFree" /proc/meminfo | awk '{print $2}')
total_mem_free_cache=$(grep "^MemAvailable" /proc/meminfo | awk '{print $2}')

free_fraction_normal=$(awk "BEGIN {printf \"%.2f\", $total_free_memory / $total_memory}")
free_fraction_with_caching_efficiency=$(awk "BEGIN {printf \"%.2f\", $total_mem_free_cache / $total_memory}")

running_processes=$(grep "^procs_running" /proc/stat | awk '{print $2}')
total_processes_since_boot=$(grep "^processes" /proc/stat | awk '{print $2}')

# printing...
echo "---System details---"
echo "Total CPU logical cores = $total_logical_cpu_sores"
echo "Total Memory = $total_memory KB"
echo "Total Free Memory = $total_free_memory KB"
echo "Total Free Memory (cache efficiency considered) = $total_mem_free_cache KB"
echo "Fraction of free memory (normal)= $free_fraction_normal KB"
echo "Fraction of free memory (caching efficiency considrered)= $free_fraction_with_caching_efficiency KB"
echo "Total no. of running processes = $running_processes"
echo "Total no. of processes since boot = $total_processes_since_boot"

echo "Analysis completed. . . "
