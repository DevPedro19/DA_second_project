# RegisterAllocation
Global register allocation program that maps registers from variable live ranges, supporting multiple algorithms (web splitting and web spilling) 
```
# -S: uses the current directory as the source directory
# -B: puts all the files on a folder called build
cmake -S . -B build
# calls the compiler to build the desired targets 
cmake --build build
# To run the tool
./RegisterAllocation
```
