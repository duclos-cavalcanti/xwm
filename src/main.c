#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "main.h"
#include "wm.h"
#include "utils.h"

#define MAX_ERROR_TEXT_LENGTH 1024

static window_manager_t* wm = { 0 };
static char err[MAX_ERROR_TEXT_LENGTH] = { 0 };

int xerror(Display* d, XErrorEvent* e) {
    XGetErrorText(d, e->error_code, err, sizeof(err));
    printf("Received X Error:\n"
           "\tRequest: %d\n"
           "\tResource ID: %d\n"
           "\tError code: %d - %s\n",
           (int) e->request_code,
           (int) e->resourceid,
           (int) e->error_code,
           err);

    return 0;
}


int start() {
    if (! ( wm->dpy = XOpenDisplay(NULL) ) ) {
        fprintf(stderr, "Failed to open XDisplay.\n");
        return EXIT_FAILURE;
    }

    wm->screen      = DefaultScreen(wm->dpy);
    wm->root        = DefaultRootWindow(wm->dpy);
    wm->width       = XDisplayWidth(wm->dpy, DefaultScreen(wm->dpy));
    wm->height      = XDisplayHeight(wm->dpy, DefaultScreen(wm->dpy));
    wm->running     = true;

    return 0;
}

int run() {
    XSetErrorHandler(&xerror);

    while(1 && wm->running) {
        XEvent e;
        XNextEvent(wm->dpy, &e);
        switch (e.type){
            case CreateNotify:
                create_notify(wm, &e);
                break;

            case ConfigureRequest:
                configure_request(wm, &e);
                break;

            default: 
                break;

        }
    }

    return EXIT_SUCCESS;
}

void close() {
    XCloseDisplay(wm->dpy);
}

int main(int argc, char* argv[]) {
    start();
    run();
    close();

    return 0;
}
