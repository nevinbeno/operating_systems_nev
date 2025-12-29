# `/proc/cpuinfo`
### Aim: 
Extract system level information directly from the kernel, and interpret it using `/proc`. 

### `/proc`
- `proc` is a virtual file system created by the linux kernel. 
- It is not something on the disk; it is the live view of the kernel data structure. 
- The data displayed is dynamic, and is based on the system condition during that moment. 
### Usage and interpreting the result: 
```bash
~$ cat /proc/cpuinfo
```
Output: 
```
benoJR:~$ cat /proc/cpuinfo
processor	: 0
vendor_id	: AuthenticAMD
cpu family	: 25
model		: 68
model name	: AMD Ryzen 7 7735HS with Radeon Graphics
stepping	: 1
microcode	: 0xa40410a
cpu MHz		: 1553.390
cache size	: 512 KB
physical id	: 0
siblings	: 16
core id		: 0
cpu cores	: 8
apicid		: 0
initial apicid	: 0
fpu		: yes
fpu_exception	: yes
cpuid level	: 16
wp		: yes
flags		: fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush mmx fxsr sse sse2 ht syscall nx mmxext fxsr_opt pdpe1gb rdtscp lm constant_tsc rep_good nopl xtopology nonstop_tsc cpuid extd_apicid aperfmperf rapl pni pclmulqdq monitor ssse3 fma cx16 sse4_1 sse4_2 x2apic movbe popcnt aes xsave avx f16c rdrand lahf_lm cmp_legacy svm extapic cr8_legacy abm sse4a misalignsse 3dnowprefetch osvw ibs skinit wdt tce topoext perfctr_core perfctr_nb bpext perfctr_llc mwaitx cpb cat_l3 cdp_l3 hw_pstate ssbd mba ibrs ibpb stibp vmmcall fsgsbase bmi1 avx2 smep bmi2 erms invpcid cqm rdt_a rdseed adx smap clflushopt clwb sha_ni xsaveopt xsavec xgetbv1 xsaves cqm_llc cqm_occup_llc cqm_mbm_total cqm_mbm_local user_shstk clzero irperf xsaveerptr rdpru wbnoinvd cppc arat npt lbrv svm_lock nrip_save tsc_scale vmcb_clean flushbyasid decodeassists pausefilter pfthreshold avic v_vmsave_vmload vgif v_spec_ctrl umip pku ospke vaes vpclmulqdq rdpid overflow_recov succor smca fsrm debug_swap
bugs		: sysret_ss_attrs spectre_v1 spectre_v2 spec_store_bypass srso ibpb_no_ret tsa vmscape
bogomips	: 6388.03
TLB size	: 2560 4K pages
clflush size	: 64
cache_alignment	: 64
address sizes	: 48 bits physical, 48 bits virtual
power management: ts ttp tm hwpstate cpb eff_freq_ro [13] [14]

processor	: 1
vendor_id	: AuthenticAMD
cpu family	: 25
model		: 68
model name	: AMD Ryzen 7 7735HS with Radeon Graphics
stepping	: 1
microcode	: 0xa40410a
cpu MHz		: 1105.000
cache size	: 512 KB
physical id	: 0
siblings	: 16
core id		: 0
cpu cores	: 8
apicid		: 1
initial apicid	: 1
fpu		: yes
fpu_exception	: yes
cpuid level	: 16
wp		: yes
flags		: fpu vme de pse tsc msr pae mce cx8 apic sep mtrr pge mca cmov pat pse36 clflush mmx fxsr sse sse2 ht syscall nx mmxext fxsr_opt pdpe1gb rdtscp lm constant_tsc rep_good nopl xtopology nonstop_tsc cpuid extd_apicid aperfmperf rapl pni pclmulqdq monitor ssse3 fma cx16 sse4_1 sse4_2 x2apic movbe popcnt aes xsave avx f16c rdrand lahf_lm cmp_legacy svm extapic cr8_legacy abm sse4a misalignsse 3dnowprefetch osvw ibs skinit wdt tce topoext perfctr_core perfctr_nb bpext perfctr_llc mwaitx cpb cat_l3 cdp_l3 hw_pstate ssbd mba ibrs ibpb stibp vmmcall fsgsbase bmi1 avx2 smep bmi2 erms invpcid cqm rdt_a rdseed adx smap clflushopt clwb sha_ni xsaveopt xsavec xgetbv1 xsaves cqm_llc cqm_occup_llc cqm_mbm_total cqm_mbm_local user_shstk clzero irperf xsaveerptr rdpru wbnoinvd cppc arat npt lbrv svm_lock nrip_save tsc_scale vmcb_clean flushbyasid decodeassists pausefilter pfthreshold avic v_vmsave_vmload vgif v_spec_ctrl umip pku ospke vaes vpclmulqdq rdpid overflow_recov succor smca fsrm debug_swap
bugs		: sysret_ss_attrs spectre_v1 spectre_v2 spec_store_bypass srso ibpb_no_ret tsa vmscape
bogomips	: 6388.03
TLB size	: 2560 4K pages
clflush size	: 64
cache_alignment	: 64
address sizes	: 48 bits physical, 48 bits virtual
power management: ts ttp tm hwpstate cpb eff_freq_ro [13] [14]
.
.
.
.
.

```
### Interpretation: 
- I got some data, which had things gettingg repeated. 
- 16 similar such instances were obtained. 
#### Processors: 
- Were numbered from 0 to 15 (like C - array indexing), and it represents **Total no. of LOGICAL CPU cores** in the system. 
- `Physical id = 0`: only one CPU socket. 
- `core id`: two processors (logical) share the same core id. This explains, to which physical core, is the logical core (thread) relateed. 
    ```
    Processor 0 and 1: core id = 0
    Processor 2 and 3: core id = 1
    .
    .
    .
    .
    Processor 14 and 15: core id: 7

    8 cores [0 to 7], and 16 threads [0 to 15]
    ```
#### Siblings, cores, threads, SMTs
- `cores = 8`: physical core count in the system
- `siblings = 16`: total siblings
- Threads per core = siblings / core = 2. The value > 1 => SMT (Simult Multi Threading)(Multi-threading is enabled)
#### CPU pov
- Model name: 
- `vendor_id`
- CPU frequency..