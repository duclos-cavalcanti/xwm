#include "utils.h"

int frame_window(window_manager_t* wm, Window* w) {
    XWindowAttributes xattr;
    XGetWindowAttributes(wm->dpy, w, &xattr);

    Window fr = XCreateSimpleWindow(wm->dpy, wm->root->win, xattr.x,
                                                            xattr.y,
                                                            xattr.width,
                                                            xattr.height,
                                                            config_def.border_width,
                                                            config_def.border_color,
                                                            config_def.bg_color);

    XSelectInput(wm->dpy, fr, SubstructureRedirectMask | SubstructureNotifyMask);
    XAddToSaveSet(wm->dpy, w);
    XReparentWindow(wm->dpy, w, fr, 0, 0);
    XMapWindow(wm->dpy, fr);
    XGrabButton(wm->dpy, Button1, Mod1Mask, w, false,
                ButtonPressMask | ButtonReleaseMask | ButtonMotionMask,
                GrabModeAsync, GrabModeAsync, None, None);

    return 0;
}

