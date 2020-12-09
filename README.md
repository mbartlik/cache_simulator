# Cache Simulator
This program accepts a memory trace text file that details memory reads and writes. The program can process this and simulate an L1 cache. The program determines if the access is a hit or miss, and will properly update the simulated cache after every line of the trace. The program can be compiled using the makefile by running the command "make".

## Input Format
./first <cache size> <associativity> <replace policy> <block size> <trace file>
* <cache size> is the total size of the cache in bytes. This number should be a power of 2.
* <associativity> is one of:
  * direct - a direct mapped cache
  * assoc - a fully associative cache
  * assoc:n - an n-way associative cache. n will be a power of 2.
* <replace policy> is the replacement policy, either lru or fifo.
* <block size> is a power of 2 integer that specifies the size of the cache block in bytes.  
* <trace file> is the name of the trace file.
