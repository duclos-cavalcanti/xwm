#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "main.h"
#include "wm.h"
#include "util.h"

static window_manager_t* wm = { 0 };

static int wm_handler(Display* d, XErrorEvent* e) {
    if (e->error_code == BadAccess) {
        wm->wm_fouund = true;
    }
    return 0;
}

int detect_wm(window_manager_t* wm) {
    XSetErrorHandler(&wm_handler);
    XSelectInput(wm->dpy,
                 wm->root->win,
                 SubstructureRedirectMask |
                 SubstructureNotifyMask);
    XSync(wm->dpy, false);

    if (wm->wm_found) return 1;
    return 0;
}


#define MAX_ERROR_TEXT_LENGTH 1024
int xerror(Display* d, XErrorEvent* e) {
    char err[MAX_ERROR_TEXT_LENGTH] = { 0 };

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
    wm->dpy = XOpenDisplay(NULL);
    if (!wm->dpy) {
        fprintf(stderr, "Failed to open XDisplay.\n");
        return EXIT_FAILURE;
    }

    wm->root        = DefaultRootWindow(wm->dpy);
    wm->clients     = new_list();
    wm->width       = XDisplayWidth(wm->dpy, DefaultScreen(wm->dpy));
    wm->height      = XDisplayHeight(wm->dpy, DefaultScreen(wm->dpy));
    wm->running     = true;
    wm->wm_found    = false;
    return 0;
}

void run() {
    if (detect_wm(wm)) return EXIT_FAILURE;
    XSetErrorHandler(&xerror);

    while(1 && wm->running) {
        XEvent e;
        XNextEvent(wm->dpy, &e);
        process_event(wm, &e);
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
