/*
 *   !!! PROVIDED FILE - DO NOT MODIFY !!!
 */
#ifndef HEXFUNCS_H
#define HEXFUNCS_H

#include <stdio.h> /* Needed for FILE* definition used below */

/* It is good practice to NOT use "magic numbers" in your source and, instead,
 * define and use well named constants for more readable, maintainable, and
 * flexible code!
 */
#define BYTES_PER_LINE 16

/* "Byte" is a more descriptive type for what we are doing. AND, recall that
 * the char type's default is compiler dependent and can be either signed or
 * unsigned by default! By defining an explicit type matching our needs and
 * using it instead of just char the code will compile the same and correctly
 * on ALL machines and, as system programmers, portability is our goal!
 */
typedef unsigned char Byte;

/* fileOpen: This function attempts to open the specified file for reading
 *           using the C Standard Library function fopen. When fopen fails 
 *           perror is called with the specified file name. Note, however,
 *           that the function does NOT terminate the program as the user may
 *           have specified additional files that can be processed.
 *
 * Return: The FILE* returned by fopen.
 */
FILE* fileOpen(const char *fname);

/* fileClose: This function attempts to close the specified FILE* using the
 *            C Standard Library function fclose. When fclose fails perror
 *            is called with the string "fileClose" and the program is
 *            terminated with a call to exit(EXIT_FAILURE). 
 *
 * Return: void
 */
void fileClose(FILE *file);

/* readBytes: This function attempts to read BYTES_PER_LINE number of bytes
 *            from the specified FILE* into the specified array. When fread
 *            fails perror is called with the string "readBytes" and the
 *            program is terminated with a call to exit(EXIT_FAILURE). Note
 *            that fread returns zero for BOTH EOF and errors - you can use
 *            ferror to distinguish EOF from an error.
 *
 * Return: The number of bytes read which MAY be less than the number requested
 *         when EOF is reached.
 */
int readBytes(FILE *file, Byte bytes[]);

/* printLine: This function prints the specified bytes as formatted hexadecimal
 *            and when a byte is printable, as determined by the C Standard
 *            Library function isprint, as an ASCII character. When a byte is
 *            not printable a period ('.') is printed in its place. See the
 *            reference solution for more details. FYI: The reference solution
 *            uses %02x as the format flag to output each byte in hex.
 *
 *            The byteCount is the number of bytes in the array that actually
 *            were read from the file. It will not always be BYTES_PER_LINE.
 *
 *            The "writtenSoFar" variable will allow you to write the first
 *            column of the expected output which is the count of the first
 *            byte on each line (also displayed in hex using %08x as the format
 *            flag).
 *
 * Return: void
 */
void printLine(Byte bytes[], int byteCount, unsigned int writtenSoFar);

#endif
