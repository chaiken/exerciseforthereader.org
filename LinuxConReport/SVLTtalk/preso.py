#!/usr/bin/env python

# python-gtk-webkit presentation program.
# Copyright (C) 2009 by Akkana Peck.
# Share and enjoy under the GPL v2 or later.

import sys, os
import gtk, gobject
import webkit

class WebBrowser(gtk.Window):
    def __init__(self, url):
        gtk.Window.__init__(self)

        # Either run fullscreen, or set the size to the size of my laptop:
        #self.set_default_size(1366,768)
        #self.set_default_size(1280,800)
        self.set_default_size(1024,768)
        self.fullscreen()

        self._browser= webkit.WebView()
        self.add(self._browser)
        self.connect('destroy', gtk.main_quit)

        self._browser.open(url)    # throw err if url isn't defined
        self.show_all()

if __name__ == "__main__":
    if len(sys.argv) <= 1 :
        print "Usage:", sys.argv[0], "url"
        sys.exit(0)

    # Figure out if it's a filename or a url
    url = sys.argv[1]
    if url.find(':') < 0 :
        if url[0] == '/' :
            url = 'file://' + url
        else :
            url = 'file://' + os.getcwd() + '/' + url

    gobject.threads_init()
    webbrowser = WebBrowser(url)
    gtk.main()

