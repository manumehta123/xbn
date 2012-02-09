# -------------------------------------------------
# Project created by QtCreator 2010-04-08T19:16:29
# -------------------------------------------------

TEMPLATE = subdirs
SUBDIRS = sub_libxbn sub_testxbn sub_xsltp sub_xpath sub_xmlos

sub_libxbn.subdir = libxbn
sub_testxbn.subdir = testxbn
sub_xsltp.subdir = xsltp
sub_xpath.subdir = xpath
sub_xmlos.subdir = xmlos

sub_libxbn.depends = 
sub_testxbn.depends = sub_libxbn
sub_xsltp.depends = sub_libxbn
sub_xpath.depends = sub_libxbn
sub_xmlos.depends = sub_libxbn

OTHER_FILES = doc/todo.txt
