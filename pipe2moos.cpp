#include <MOOS/libMOOS/Comms/MOOSAsyncCommClient.h>

int main(int argc, char ** const argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s moos_app_name key_to_publish\n", argv[0]);
        return 1;
    }

    /* shut off cout, since libmoos writes a lot of diagnostic text to it */
    std::cout.rdbuf(nullptr);
    std::cerr.rdbuf(nullptr);

    /* make sure input is still line buffered even when piped */
    setvbuf(stdin, NULL, _IOLBF, 0);

    MOOS::MOOSAsyncCommClient Comms;
    Comms.Run("localhost", 9000, argv[1]);
    Comms.WaitUntilConnected(-1);

    /* loop over lines of input on stdin */
    char * line = NULL;
    size_t linecap = 0;
    while (getline(&line, &linecap, stdin) > 0) {
        /* strip newline off input */
        char * newline = strchr(line, '\n');
        if (newline) *newline = '\0';

        Comms.Notify(argv[2], line);
    }

    /* cleanup. we get here when the above loop exits, due to eof on stdin */
    Comms.Close();
    free(line);
}
