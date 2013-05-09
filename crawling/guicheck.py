#! /usr/bin/python
# -*- coding: utf-8 -*-

import sys
import codecs
from gi.repository import Gtk, Gdk

valid = []

def main ():
    global valid
    if len(sys.argv) != 3:
        print "Usage: %s inputFile outputFile" %sys.argv[0]
        sys.exit (1)

    ifile = codecs.open (sys.argv[1], 'r', encoding='utf-8')
    words = ifile.readlines ()
    ifile.close ()

    with codecs.open (sys.argv[2], 'r', encoding='utf-8') as ofile:
        for line in (l.strip() for l in ofile):
            valid.append (line)

    valid.sort ()
    existings = { x : True for x in valid }
    #ofile = codecs.open (sys.argv[2], 'a', encoding='utf-8')

    model = Gtk.ListStore (int, str, str)
    for k, iline in enumerate(l.strip() for l in words):
        if iline in existings:
            model.append ([k, iline, Gtk.STOCK_OK])
        else:
            model.append ([k, iline, None])
    treeview = Gtk.TreeView (model)
    renderer = Gtk.CellRendererText()
    column = Gtk.TreeViewColumn("#", renderer, text=0)
    treeview.append_column(column)

    renderer = Gtk.CellRendererPixbuf ()
    column = Gtk.TreeViewColumn ("Status", renderer,icon_name=2)
    #column.set_sizing (Gtk.TreeViewColumnSizing.FIXED)
    treeview.append_column(column)

    renderer = Gtk.CellRendererText()
    column = Gtk.TreeViewColumn("Word", renderer, text=1)
    treeview.append_column(column)

    scroll = Gtk.ScrolledWindow ()
    scroll.add (treeview)

    window = Gtk.Window ()
    window.add (scroll)
    window.set_default_size (400, 600)
    window.set_border_width (5)
    window.show_all ()

    window.connect ("delete-event", on_quit, None)
    treeview.connect ("row-activated", on_row_activated, model)
    Gtk.init (sys.argv)
    Gtk.main ()

def on_row_activated (view, path, column, model):
    iter_ = model.get_iter (path)
    text  = model.get (iter_, 1)[0].decode ('utf8')

    valid.append (text)
    model.set (iter_, 2, Gtk.STOCK_OK)

def on_quit (widget, event, data):
    global valid
    valid.sort ()
    valid = set(valid)

    with codecs.open (sys.argv[2], 'w', encoding='utf-8') as ofile:
        for each in valid:
            ofile.write (each + '\n')

    Gtk.main_quit ()

if __name__ == "__main__":
    main ()
