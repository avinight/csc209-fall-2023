#include "request.h"
#include "response.h"
#include <string.h>


/******************************************************************************
 * ClientState-processing functions
 *****************************************************************************/
ClientState *init_clients(int n) {
    ClientState *clients = malloc(sizeof(ClientState) * n);
    for (int i = 0; i < n; i++) {
        clients[i].sock = -1;  // -1 here indicates available entry
    }
    return clients;
}

/* 
 * Remove the client from the client array, free any memory allocated for
 * fields of the ClientState struct, and close the socket.
 */
void remove_client(ClientState *cs) {
    if (cs->reqData != NULL) {
        free(cs->reqData->method);
        free(cs->reqData->path);
        for (int i = 0; i < MAX_QUERY_PARAMS && cs->reqData->params[i].name != NULL; i++) {
            free(cs->reqData->params[i].name);
            free(cs->reqData->params[i].value);
        }
        free(cs->reqData);
        cs->reqData = NULL;
    }
    close(cs->sock);
    cs->sock = -1;
    cs->num_bytes = 0;
}


/*
 * Search the first inbuf characters of buf for a network newline ("\r\n").
 * Return the index *immediately after* the location of the '\n'
 * if the network newline is found, or -1 otherwise.
 * Definitely do not use strchr or any other string function in here. (Why not?)
 */
int find_network_newline(const char *buf, int inbuf) {
    
    //IMPLEMENT THIS
    int i;
    for (i = 0; i < inbuf - 1; i++) {
        if (buf[i] == '\r' && buf[i + 1] == '\n') {
            return i + 2;
        }
    }
    return -1;
}

/*
 * Removes one line (terminated by \r\n) from the client's buffer.
 * Update client->num_bytes accordingly.
 *
 * For example, if `client->buf` contains the string "hello\r\ngoodbye\r\nblah",
 * after calling remove_line on it, buf should contain "goodbye\r\nblah"
 * Remember that the client buffer is *not* null-terminated automatically.
 */
void remove_buffered_line(ClientState *client) {
    
    //IMPLEMENT THIS
    int where = find_network_newline(client->buf, client->num_bytes);
    if (where > 0) {
        client->buf[where - 2] = '\0';
        memmove(client->buf, client->buf + where, client->num_bytes - where);
        client->num_bytes -= where;
    }
}


/*
 * Read some data into the client buffer. Append new data to data already
 * in the buffer.  Update client->num_bytes accordingly.
 * Return the number of bytes read in, or -1 if the read failed.

 * Be very careful with memory here: there might be existing data in the buffer
 * that you don't want to overwrite, and you also don't want to go past
 * the end of the buffer, and you should ensure the string is null-terminated.
 */
int read_from_client(ClientState *client) {
    
    //IMPLEMENT THIS
    int *inbuf = &client->num_bytes;           // How many bytes currently in buffer?
    int room = sizeof(client->buf) - *inbuf;   // How many bytes remaining in buffer?
    char *after = client->buf + *inbuf;        // Pointer to position after the data in buf

    int nbytes = read(client->sock, after, room);
    if (nbytes < 0) {
        perror("read");
        return -1;
    }
    if (nbytes > 0) {
        *inbuf += nbytes;
        client->buf[*inbuf] = '\0';
        return nbytes;
    }
    return 0;
}


/*****************************************************************************
 * Parsing the start line of an HTTP request.
 ****************************************************************************/
// Helper function declarations.
void parse_query(ReqData *req, const char *str);
void update_fdata(Fdata *f, const char *str);
void fdata_free(Fdata *f);
void log_request(const ReqData *req);


/* If there is a full line (terminated by a network newline (CRLF)) 
 * then use this line to initialize client->reqData
 * Return 0 if a full line has not been read, 1 otherwise.
 */
int parse_req_start_line(ClientState *client) {

    //IMPLEMENT THIS
    char *buf = client->buf; // The request buffer

    // Find the end of the line
    int where = find_network_newline(buf, client->num_bytes);
    if (where < 0) {
        return 0;
    }

    // Replace the network newline with a null terminator
    buf[where - 2] = '\0';

    // Parse the method, path, and query string
    char *method = strtok(buf, " ");
    char *path = strtok(NULL, " ");
    char *query = strchr(path, '?');

    // If there is a query string, remove the '?' so that path is just the path
    if (query != NULL) {
        *query = '\0';
        query++;
    }
    
    // Initialize the client's request data struct
    client->reqData = malloc(sizeof(ReqData));
    if (client->reqData == NULL) {
        perror("malloc");
        exit(1);
    }

    for (int i = 0; i < MAX_QUERY_PARAMS; i++) {
        client->reqData->params[i].name = NULL;
        client->reqData->params[i].value = NULL;
        // fdata_free(&client->reqData->params[i]);
    }

    client->reqData->method = malloc(strlen(method) + 1);
    if (client->reqData->method == NULL) {
        perror("malloc");
        exit(1);
    }
    strncpy(client->reqData->method, method, strlen(method) + 1);
    client->reqData->method[strlen(method)] = '\0';

    client->reqData->path = malloc(strlen(path) + 1);
    if (client->reqData->path == NULL) {
        perror("malloc");
        exit(1);
    }
    strncpy(client->reqData->path, path, strlen(path) + 1);
    client->reqData->path[strlen(path)] = '\0';

    // Parse the query string
    if (query != NULL){
        parse_query(client->reqData, query);
    }

    // Restore the network newline character
    client->buf[where - 2] = '\r';
    // Remove the line from the buffer
    remove_buffered_line(client);

    // This part is just for debugging purposes.
    log_request(client->reqData);
    return 1;
}

/*
 * Update the given Fdata struct with the key-value pair contained in the given
 */
void update_fdata(Fdata *f, const char *str) {
    int where = strrchr(str, '=') - str;
    
    char *str_copy = malloc(strlen(str) + 1);
    if (str_copy == NULL) {
        perror("malloc");
        exit(1);
    }
    strncpy(str_copy, str, strlen(str) + 1);
    str_copy[strlen(str)] = '\0';

    char *name = str_copy;
    name[where] = '\0';
    char *value = &str_copy[where + 1];
    value[strlen(value)] = '\0';

    if (name && value) {
        f->name = malloc(strlen(name) + 1);
        if (f->name == NULL) {
            perror("malloc");
            exit(1);
        }
        strncpy(f->name, name, strlen(name) + 1);
        f->name[strlen(name)] = '\0';

        f->value = malloc(strlen(value) + 1);
        if (f->value == NULL) {
            perror("malloc");
            exit(1);
        }
        strncpy(f->value, value, strlen(value) + 1);
        f->value[strlen(value)] = '\0';
    }
    free(str_copy);
}

/*
 * Free all memory allocated in the given Fdata struct.
 */
void fdata_free(Fdata *f) {
    free(f->name);
    free(f->value);
}

/*
 * Initializes req->params from the key-value pairs contained in the given 
 * string.
 * Assumes that the string is the part after the '?' in the HTTP request target,
 * e.g., name1=value1&name2=value2.
 */
void parse_query(ReqData *req, const char *str) {
    
    //IMPLEMENT THIS
    char *str_copy = malloc(strlen(str) + 1);
    if (str_copy == NULL) {
        perror("malloc");
        exit(1);
    }
    strncpy(str_copy, str, strlen(str) + 1);
    str_copy[strlen(str)] = '\0';
    char *pair = strtok(str_copy, "&");

    int i = 0;
    while (pair != NULL && i < MAX_QUERY_PARAMS) {
        update_fdata(&req->params[i], pair);
        pair = strtok(NULL, "&");
        i++;
    }
    free(str_copy);
}


/*
 * Print information stored in the given request data to stderr.
 */
void log_request(const ReqData *req) {
    fprintf(stderr, "Request parsed: [%s] [%s]\n", req->method, req->path);
    for (int i = 0; i < MAX_QUERY_PARAMS && req->params[i].name != NULL; i++) {
        fprintf(stderr, "  %s -> %s\n", 
                req->params[i].name, req->params[i].value);
    }
}


/******************************************************************************
 * Parsing multipart form data (image-upload)
 *****************************************************************************/

char *get_boundary(ClientState *client) {
    int len_header = strlen(POST_BOUNDARY_HEADER);

    while (1) {
        int where = find_network_newline(client->buf, client->num_bytes);
        if (where > 0) {
            if (where < len_header || strncmp(POST_BOUNDARY_HEADER, client->buf, len_header) != 0) {
                remove_buffered_line(client);
            } else {
                // We've found the boundary string!
                // We are going to add "--" to the beginning to make it easier
                // to match the boundary line later
                char *boundary = malloc(where - len_header + 2);
                strncpy(boundary, "--", where - len_header + 1);
                strncat(boundary, client->buf + len_header, where - len_header - 1);
                boundary[where - len_header] = '\0';
                return boundary;
            }
        } else {
            // Need to read more bytes
            if (read_from_client(client) <= 0) {
                // Couldn't read; this is a bad request, so give up.
                return NULL;
            }
        }
    }
    return NULL;
}


char *get_bitmap_filename(ClientState *client, const char *boundary) {
    int len_boundary = strlen(boundary);

    // Read until finding the boundary string.
    while (1) {
        int where = find_network_newline(client->buf, client->num_bytes);
        if (where > 0) {
            if (where < len_boundary + 2 ||
                    strncmp(boundary, client->buf, len_boundary) != 0) {
                remove_buffered_line(client);
            } else {
                // We've found the line with the boundary!
                remove_buffered_line(client);
                break;
            }
        } else {
            // Need to read more bytes
            if (read_from_client(client) <= 0) {
                // Couldn't read; this is a bad request, so give up.
                return NULL;
            }
        }
    }

    int where = find_network_newline(client->buf, client->num_bytes);

    client->buf[where-1] = '\0';  // Used for strrchr to work on just the single line.
    char *raw_filename = strrchr(client->buf, '=') + 2;
    int len_filename = client->buf + where - 3 - raw_filename;
    char *filename = malloc(len_filename + 1);
    strncpy(filename, raw_filename, len_filename);
    filename[len_filename] = '\0';

    // Restore client->buf
    client->buf[where - 1] = '\n';
    remove_buffered_line(client);
    return filename;
}

/*
 * Read the file data from the socket and write it to the file descriptor
 * file_fd.
 * You know when you have reached the end of the file in one of two ways:
 *    - search for the boundary string in each chunk of data read 
 * (Remember the "\r\n" that comes before the boundary string, and the 
 * "--\r\n" that comes after.)
 *    - extract the file size from the bitmap data, and use that to determine
 * how many bytes to read from the socket and write to the file
 */
int save_file_upload(ClientState *client, const char *boundary, int file_fd) {
    // Read in the next two lines: Content-Type line, and empty line
    remove_buffered_line(client);
    remove_buffered_line(client);

    // IMPLEMENT THIS
    int nbytes;
    while ((nbytes = read_from_client(client)) > 0) {
        int where;
        while ((where = find_network_newline(client->buf, client->num_bytes)) > 0) {
            // Check if we've reached the end of the file
            if (strstr(client->buf + where, boundary) != NULL) {
                write(file_fd, client->buf, where - 2);
                return 0;
            }
            // Write to file
            write(file_fd, client->buf, where);
            // Remove the line from the buffer
            remove_buffered_line(client);
            // Update nbytes
            nbytes -= where;
        }
        // If buffer is full, write half of it to file
        if (client->num_bytes == sizeof(client->buf)) {
            write(file_fd, client->buf, client->num_bytes / 2);
            memmove(client->buf, client->buf + client->num_bytes / 2, client->num_bytes / 2);
            client->num_bytes = client->num_bytes / 2;
        }
    }
    return -1;
}

