#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/mman.h>

#include "lexer.h"

int goatLexer( char* sourceFileName ) {
    int fp;
    size_t size;
    char *curr, *end;
    CodePoint cp;

    fp = open(sourceFileName, O_RDONLY);

    if(fp == -1) {
        printf("Unable to open source file: %s\n", sourceFileName);
        return 0;
    }

    size = goatGetFileSize( fp );
    
    curr = goatMapFileToMemory( fp, size );
    if(curr == MAP_FAILED) {
        return 0;
    }

    // Calculate the end of the buffer
    end = curr + size;

    while (curr < end) {
        goatGetNextCodePoint( &cp, &curr, &end);
        printf("%s", cp.utf8);
    }
    
    return 1;
}

// Returns the size of the source file, so that we know
// how large a memory block to map to.
size_t goatGetFileSize( int fp ) {
    struct stat sb;

    if(fstat(fp, &sb) == -1) {
        printf("Error getting file stat");
        return -1;
    }
    return sb.st_size;
}


// Creates a mapping between the source file on disk and the buffer in memory.
char *goatMapFileToMemory( int fp, size_t len) {
    char *buffer;
    buffer = (char *) mmap( NULL, len, PROT_READ, MAP_SHARED, fp, 0);
    if (buffer == MAP_FAILED) {
        printf("Map failed\n");
        return MAP_FAILED;
    }
    return buffer;
}


// goatGetNextCodePoint takes a pointer to a CodePoint structure, and then
// copies the next codepoint found in the UTF8 encoded buffer to it. It
// increments the pointer into the buffer automatically.
void goatGetNextCodePoint(CodePoint *cp, char **curr, char **end) {
    memset(cp, 0, sizeof(CodePoint));

    // Test we don't go beyond the end of the file.
    if (*curr > *end) {
        printf("Passed end of code block\n");
        return;
    }

    // Convert the character, fill the CodePoint struct and increment
    // the buffer pointers as required
    if ((**curr & 0x80) == 0) {
        // It's a single-byte ASCII charater
        cp->utf8[0] = **curr;
        cp->wchar = (w_char) (cp->utf8[0] & 0x3F);
    } else if ((**curr & 0xE0) == 0xC0) {
        // 2-byte character;
        // TODO: Check that the 2-byte character doesn't take us beyond the
        // end of the buffer.
        cp->utf8[0] = **curr;
        cp->utf8[1] = *(++(*curr));
        cp->wchar = (((w_char) (cp->utf8[0] & 0x1F)) << 6) |
                    ((w_char) (cp->utf8[1] & 0x3F));
    } else if ((**curr & 0xF0) == 0xE0) {
        // 3-byte character
        cp->utf8[0] = **curr;
        cp->utf8[1] = *(++(*curr));
        cp->utf8[2] = *(++(*curr));
        cp->wchar = (((w_char) (cp->utf8[0] & 0x0F)) << 12) |
                    (((w_char) (cp->utf8[1] & 0x3F)) << 6) |
                    ((w_char) (cp->utf8[2] & 0x3F));
    } else if ((**curr & 0xF8) == 0xF0) {
        // 4-byte character
        cp->utf8[0] = **curr;
        cp->utf8[1] = *(++(*curr));
        cp->utf8[2] = *(++(*curr));
        cp->utf8[3] = *(++(*curr));
        cp->wchar = (((w_char) (cp->utf8[0] & 0x07)) << 18) |
                    (((w_char) (cp->utf8[0] & 0x3F)) << 12) |
                    (((w_char) (cp->utf8[1] & 0x3F)) << 6) |
                    ((w_char) (cp->utf8[2] & 0x3F));
    } else {
        printf("Invalid code point\n");
    }
    ++(*curr);
}