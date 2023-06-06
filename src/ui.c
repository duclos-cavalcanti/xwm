#include "ui.h"
#include "config.h"

int frame_window(window_manager_t* wm, window_t* w) {
    XWindowAttributes xattr;
    XGetWindowAttributes(wm->dpy, w->win, &xattr);

    Window fr = XCreateSimpleWindow(wm->dpy, wm->root->win, xattr.x,
                                                            xattr.y,
                                                            xattr.width,
                                                            xattr.height,
                                                            config_def.border_width,
                                                            config_def.border_color,
                                                            config_def.bg_color);

    XSelectInput(wm->dpy, fr, SubstructureRedirectMask | SubstructureNotifyMask);
    XAddToSaveSet(wm->dpy, w->win);
    XReparentWindow(wm->dpy, w->win, fr, 0, 0);
    XMapWindow(wm->dpy, fr);
    XGrabButton(wm->dpy, Button1, Mod1Mask, w->win, false,
                ButtonPressMask | ButtonReleaseMask | ButtonMotionMask,
                GrabModeAsync, GrabModeAsync, None, None);

    return 0;
}

