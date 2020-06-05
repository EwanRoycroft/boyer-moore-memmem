#include <string.h> 
#include <stdio.h> 

#define _NUM_CHARS 256
int _bad_chars[_NUM_CHARS];

// A utility function to get maximum of two integers 
static int _max(int a, int b) { return (a > b) ? a : b; } 

static void _fill_table(char *needle, size_t needlelen) {
    int c_idx; 
  
    // Initialize all occurrences as -1 
    for (c_idx = 0; c_idx < _NUM_CHARS; c_idx++) 
        _bad_chars[c_idx] = -1; 
  
    /* Fill the actual value of last occurrence  
     * of a character */
    for (c_idx = 0; c_idx < needlelen; c_idx++) 
        _bad_chars[(int)needle[c_idx]] = c_idx; 
}

static void *_memmem_bm(void *haystack, size_t haystacklen,
                        void *needle, size_t needlelen) {
    /* memmem using Boyer-Moore algorithm:
     * Find the first occurance of the needle in the haystack */

    _fill_table(needle, needlelen);
    
    int pos = 0;  // Position of the needle with respect to haystack 

    while (pos <= (haystacklen - needlelen)) { 
        int n_idx = needlelen - 1; 

        printf("\n%s\n", (char*)haystack);
        for (int i = 0; i < pos; i++)
            printf(" ");
        printf("%s\n\n", (char*)needle);
  
        /* Keep reducing index n_idx of needle while  
           characters of needle and haystack are  
           matching at this pos */
        while (n_idx >= 0 && 
               ((char*)needle)[n_idx] == ((char*)haystack)[pos + n_idx]) 
            n_idx--; 
  
        /* If the needle is present at current 
           pos, then index n_idx will become -1 after 
           the above loop */
        if (n_idx < 0) {
            printf("needle occurs at position = %d\n", pos);   
            break;
        } else {
            int h_int = (int)((char*)haystack)[pos + n_idx];

            if (h_int >= _NUM_CHARS || _bad_chars[h_int] == -1) {
                pos += needlelen;
                printf("shifting %d\n", needlelen);
            }
            else {
                pos += _max(1, n_idx - _bad_chars[h_int]); 
                printf("shifting %d\n", _max(1, n_idx - _bad_chars[h_int]));
            }
        }
    } 
    return haystack + pos;
}

static void _fill_table_r(char *needle, size_t needlelen) {
    int c_idx; 
  
    // Initialize all occurrences as -1 
    for (c_idx = 0; c_idx < _NUM_CHARS; c_idx++) 
        _bad_chars[c_idx] = -1; 
  
    /* Fill the actual value of first occurrence  
     * of a character */
    for (c_idx = needlelen - 1; c_idx >= 0; c_idx--) 
        _bad_chars[(int)needle[c_idx]] = c_idx; 
}

static void *_memmem_rbm(void *haystack, size_t haystacklen,
                         void *needle, size_t needlelen) {
    /* Reverse memmem using Boyer-Moore algorithm:
     * Find the last occurance of the needle in the haystack */

    _fill_table_r(needle, needlelen);
    
    int pos = haystacklen - needlelen;  // Position of the needle with respect to haystack 

    while (pos >= 0) { 
        int n_idx = 0; 

        printf("\n%s\n", (char*)haystack);
        for (int i = 0; i < pos; i++)
            printf(" ");
        printf("%s\n\n", (char*)needle);

        while (n_idx < needlelen && 
               ((char*)needle)[n_idx] == ((char*)haystack)[pos + n_idx]) 
            n_idx++; 

        if (n_idx >= needlelen) {
            printf("needle occurs at position = %d\n", pos);   
            break;
        } else {
            int h_int = (int)((char*)haystack)[pos + n_idx];

            if (h_int >= _NUM_CHARS || _bad_chars[h_int] == -1) {
                pos -= needlelen;
                printf("shifting %d\n", needlelen);
            }
            else {
                pos -= _max(1, n_idx - _bad_chars[h_int]); 
                printf("shifting %d\n", _max(1, n_idx - _bad_chars[h_int]));
            }
        }
    } 
    return haystack + pos;
}

int main() {
    char haystack1[] = "THIS IS A TEST"; 
    char needle1[]   = "TEST"; 
    _memmem_bm(haystack1, strlen(haystack1), needle1, strlen(needle1)); 

    char haystack2[] = "TSET A SI SIHT"; 
    char needle2[]   = "TSET"; 
    _memmem_rbm(&haystack2, strlen(haystack2), &needle2, strlen(needle2)); 

    return 0; 
}
