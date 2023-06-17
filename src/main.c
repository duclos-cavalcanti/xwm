#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "main.h"
#include "events.h"
#include "utils.h"

window_manager_t* wm = { 0 };

int xerror(Display* d, XErrorEvent* e) {
    static char err[500] = { 0 };

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

    wm->root        = DefaultRootWindow(wm->dpy);
    wm->width       = XDisplayWidth(wm->dpy, DefaultScreen(wm->dpy));
    wm->height      = XDisplayHeight(wm->dpy, DefaultScreen(wm->dpy));
    wm->running     = true;

    return 0;
}

int run() {
    XSetErrorHandler(&xerror);

    static void (*event_table[LASTEvent])(const XEvent *e) = {
        [CreateNotify]     = create_notify,
        [ConfigureRequest] = configure_request,
        [KeyPress] = key_press,
    };

    while(1 && wm->running) {
        XEvent e;
        XNextEvent(wm->dpy, &e);
        if (event_table[e.type]) {
            event_table[e.type](&e);
            XSync(wm->dpy, False);
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
