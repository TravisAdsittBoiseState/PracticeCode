# Makefile and Library
  This directory is simply a practice of Makefile's and the use of precompiled libraries in C
  
## Compile
  make
  
## Run
  ./main

## Notes
  Used the Rabin-Karp algorithm for a substring search, I am slowly correcting things with it
to improve runtime. Right now as it stands the algorithm is functioning fine. However, the 
hash function still prevents the algorithm from running full speed with the for loop that
is used to add the ASCII values. 

  I am going to leave the current method in the file, just comment it out because I want to
show how it is using a library and functions fine. If the hash function were in a black 
box sort of library it would require testing to see if it was running at a sufficient speed, 
but because I wrote it and have the source code I know that it is inefficient.
