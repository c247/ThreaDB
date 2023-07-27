# ThreaDB
Multi-threaded B-Plus Tree Key Value store database implementation using C++


## Parallel Searching
The B+ tree implementation supports parallel searching for multiple keys using multiple threads. When searching for multiple keys simultaneously, each key is searched using a separate thread to improve search performance. The results of each search are printed as the threads finish their search operations.

## Thread Safety
The B+ tree implementation ensures thread safety for insertions and searching using locks. When inserting key-value pairs, an exclusive lock is acquired to ensure that only one thread can insert at a time. When searching for keys, a shared lock is acquired to allow multiple threads to search concurrently.
