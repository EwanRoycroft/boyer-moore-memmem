# Boyer-Moore `memmem`
A faster alternative to the C standard [`memmem`](https://man7.org/linux/man-pages/man3/memmem.3.html) function.

Includes two functions: one searches forward from the beginning of the haystack to find the first occurrence of the needle, 
the other searches from the end of the haystack to find the last occurrence of the needle.

## Demo
```shell
$ gcc bm-memmem.c -o demo
$ ./demo
```
