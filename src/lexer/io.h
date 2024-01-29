/**
** \file io.h
** \brief Provide a defintion of an 'input' for standardize this shell input.
** \date 2024-01-27
*/

#ifndef IO_H
#define IO_H

/**
** \brief Defines the size of the internal buffer of the 'input'.
*/
#define INPUT_BUF_SIZE 128

#include <stddef.h>
#include <stdio.h>

/**
** \struct input
** \brief Represents the input of the shell.
**
** This structure is used to manage and process the input received by the shell.
** It contains a buffer to hold the input, along with metadata like the number
** of bytes read and the current position in the input.
*/
struct input
{
    FILE *stream; /** The FILE pointer that represents the input stream. Must
                     not be NULL. */
    char buf[INPUT_BUF_SIZE]; /** The internal buffer of the input. */
    size_t readed; /** The number of bytes readed after a call of 'input_read'.
                      Must be less than or equals to INPUT_BUF_SIZE. */
    size_t offset; /** Represents the position in the input. Must be less to
                      'readed' field.*/
};

/**
** \brief Creates an 'input' structure for a file-based script.
**
** This function attempts to open a file with the given filename in read mode
** and initializes an 'input' structure for it. The function dynamically
** allocates memory for the 'input' structure and initializes its 'stream'
** member to point to the opened file. If the file cannot be opened or if memory
** allocation fails, appropriate error messages are printed.
**
** \param filename A pointer to a string representing the name of the file. This
** string should not be NULL and should point to a valid, null-terminated string
** containing the file name.
** @return On success, returns a pointer to the initialized 'input' structure.
** On failure, if the file cannot be opened or memory allocation fails, returns
** NULL. In the case of memory allocation failure, an error message is printed
** to stderr using perror().
**
** \note
** - The function sets 'errno' to 0 at the beginning and uses it to check for
** file opening errors. Thus, it may alter the global 'errno' value.
** - The caller is responsible for freeing the allocated 'input' structure by
** calling 'input_free' function when it is no longer needed.
*/
struct input *input_from_file(const char *filename);

/**
** \brief Creates an 'input' structure for standard input (stdin).
**
** This function dynamically allocates memory for an 'input' structure and sets
** its 'stream' member to point to the standard input (stdin). This allows the
** shell to read input from the terminal or any other source redirected to
** stdin. If memory allocation fails, an error message is printed using
** perror().
**
** \return On success, returns a pointer to the initialized 'input' structure
** with 'stream' set to stdin. On failure, specifically if memory allocation
** fails, returns NULL and prints an error message to stderr.
**
** \note
** - The function sets 'errno' to 0 at the beginning and checks it only for
** memory allocation failures. Thus, it may alter the global 'errno' value.
** - The caller is responsible for freeing the allocated 'input' structure by
** calling 'input_free' function when it is no longer needed.
*/
struct input *input_from_stdin(void);

/**
** \brief Creates an 'input' structure for a given string.
**
** This function creates a read-only memory buffer stream from the provided
** string and initializes an 'input' structure for it. The function uses
** 'fmemopen' to create a FILE stream from the memory buffer containing the
** string, allowing the shell to read input as if it were reading from a file.
** It dynamically allocates memory for the 'input' structure and initializes its
** 'stream' member to point to the created memory buffer stream. If memory
** allocation or stream creation fails, appropriate error messages are printed.
**
** \param input A pointer to a null-terminated string that will be used as the
** input source. This string should not be NULL and should point to a valid
** string.
** \return On success, returns a pointer to the initialized 'input' structure
** with 'stream' set to the memory buffer stream. On failure, specifically if
** memory allocation fails or if 'fmemopen' fails, returns NULL and prints an
** error message to stderr.
**
** \note
** - The function sets 'errno' to 0 at the beginning and checks it for errors in
**   'fmemopen' and memory allocation. Thus, it may alter the global 'errno'
** value.
** - The caller is responsible for freeing the allocated 'input' structure by
** calling 'input_free' function when it is no longer needed.
** - The input string must remain valid and unchanged for the duration of the
** 'input' structure's use, as the underlying FILE stream refers directly to
** this string.
*/
struct input *input_from_string(char *input);

/**
** \brief Reads data into the buffer of an 'input' structure and updates its
** status.
**
** This function reads data from the 'stream' member of the provided 'input'
** structure into its internal buffer, up to the size of the buffer defined by
** 'INPUT_BUF_SIZE'. It is typically used to fetch the next chunk of data from
** the input source (like a file or a memory buffer stream) into the input
** structure for further processing. The function updates the 'readed' field of
** the 'input' structure with the number of characters read.
**
** @param input A pointer to the 'input' structure whose buffer will be filled
** with data. The 'input' structure should have been previously initialized and
** its 'stream' member should be set to a valid input source.
** @return Returns 0 if the end of the file is reached or if there's no more
** data to read. Returns 1 if data is successfully read into the buffer. On
** error (like if the 'stream' is invalid or if a read error occurs), prints an
** error message to stderr and returns -1.
**
** \note
** - The 'input' structure's 'readed' field is updated with the number of
** characters read.
** - This function does not perform null-termination on the read data. The
** 'readed' field of the 'input' structure should be used to determine the
** amount of data read.
** - In case of an error, this function prints an appropriate error message to
** stderr.
*/
int input_read(struct input *input);

/**
** \brief Reads the next character from the input buffer of an 'input'
** structure.
**
** This function retrieves the next character from the input's buffer. If the
** current offset is at or beyond the number of bytes already read into the
** buffer, it attempts to read more data into the buffer by calling
** 'input_read'. The function handles different return values from 'input_read'
** to decide the character to return or whether to indicate an error.
**
** \param input A pointer to an 'input' structure from which the character is to
** be read. This structure should have been previously initialized with a valid
** input source.
** \return Returns the next character in the buffer if available. If
** 'input_read' is called and it returns 0 (indicating end of file or no more
** data), this function returns '\0'. If 'input_read' returns -1 (indicating an
** error), this function returns -1. If the next character is successfully read,
** it is returned as an unsigned char cast to an int.
**
** \note
** - The function updates the 'offset' field of the 'input' structure after
** reading a character.
** - This function may call 'input_read' to refill the buffer if necessary.
** Therefore, it can also return '\0' or -1 based on the outcome of
** 'input_read'.
*/
char input_readchar(struct input *input);

/**
** \brief Frees the memory and resources associated with an 'input' structure.
**
** This function is responsible for releasing the resources associated with an
** 'input' structure. It first checks if the given 'input' pointer is NULL, and
** if so, it immediately returns without doing anything. Otherwise, it closes
** the associated 'stream' (if it is not NULL) using 'fclose' and then frees the
** memory allocated for the 'input' structure itself using 'free'. This function
** should be called to clean up an 'input' structure when it is no longer
** needed, to avoid memory leaks.
**
** \param input A pointer to the 'input' structure to be freed. If this pointer
** is NULL, the function does nothing.
**
** \note
** - The function safely handles NULL pointers by simply returning, making it
** robust against multiple free attempts or freeing uninitialized pointers.
** - The caller must ensure that the 'input' structure is not used after calling
** this function as it frees the memory and closes the stream.
** - If the 'input' structure has an associated 'stream', it is closed using
** 'fclose', which is a standard library function for closing open file streams.
*/
void input_free(struct input *input);

#endif /* ! IO_H */
