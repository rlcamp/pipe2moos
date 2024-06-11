#include <MOOS/libMOOS/Comms/MOOSCommClient.h>
#include <pthread.h>

static bool OnMail(void * pv) {
    CMOOSCommClient * Comms = reinterpret_cast<CMOOSCommClient*>(pv);

    MOOSMSG_LIST M;
    Comms->Fetch(M);

    /* write each message to stdout, newline delimited */
    for (MOOSMSG_LIST::iterator q = M.begin(); q != M.end(); q++)
        puts((*q).GetString().c_str());

    return true;
}

int main(const int argc, char ** const argv) {
    if (argc < 3) {
        fprintf(stderr, "Usage: %s moos_app_name key_to_subscribe_to\n", argv[0]);
        return 1;
    }

    /* shut off cout, since libmoos writes a lot of diagnostic text to it */
    std::cout.rdbuf(nullptr);
    std::cerr.rdbuf(nullptr);

    /* make sure output is still line buffered even when piped */
    setvbuf(stdout, NULL, _IOLBF, 0);

    CMOOSCommClient * Comms = new CMOOSCommClient;
    Comms->SetOnMailCallBack(OnMail, Comms);
    Comms->Run("localhost", 9000, argv[1]);
    Comms->WaitUntilConnected(-1);
    Comms->Register(argv[2], 0.0);

    /* nothing further to do in main() */
    pthread_exit(NULL);
}
