#############################################################################
# Makefile for building: xbn
# Generated by qmake (2.01a) (Qt 4.8.0) on: Fri Feb 10 00:19:49 2012
# Project:  xbn.pro
# Template: subdirs
# Command: /usr/bin/qmake -spec /usr/share/qt/mkspecs/linux-g++ -o Makefile xbn.pro
#############################################################################

first: make_default
MAKEFILE      = Makefile
QMAKE         = /usr/bin/qmake
DEL_FILE      = rm -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
COPY          = cp -f
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
INSTALL_FILE  = install -m 644 -p
INSTALL_PROGRAM = install -m 755 -p
INSTALL_DIR   = $(COPY_DIR)
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p
SUBTARGETS    =  \
		sub-libxbn \
		sub-testxbn \
		sub-xsltp \
		sub-xpath \
		sub-xmlos

libxbn/$(MAKEFILE): 
	@$(CHK_DIR_EXISTS) libxbn/ || $(MKDIR) libxbn/ 
	cd libxbn/ && $(QMAKE) /home/kraus/workspace/xbn/libxbn/libxbn.pro -spec /usr/share/qt/mkspecs/linux-g++ -o $(MAKEFILE)
sub-libxbn-qmake_all:  FORCE
	@$(CHK_DIR_EXISTS) libxbn/ || $(MKDIR) libxbn/ 
	cd libxbn/ && $(QMAKE) /home/kraus/workspace/xbn/libxbn/libxbn.pro -spec /usr/share/qt/mkspecs/linux-g++ -o $(MAKEFILE)
sub-libxbn: libxbn/$(MAKEFILE) FORCE
	cd libxbn/ && $(MAKE) -f $(MAKEFILE)
sub-libxbn-make_default: libxbn/$(MAKEFILE) FORCE
	cd libxbn/ && $(MAKE) -f $(MAKEFILE) 
sub-libxbn-make_first: libxbn/$(MAKEFILE) FORCE
	cd libxbn/ && $(MAKE) -f $(MAKEFILE) first
sub-libxbn-all: libxbn/$(MAKEFILE) FORCE
	cd libxbn/ && $(MAKE) -f $(MAKEFILE) all
sub-libxbn-clean: libxbn/$(MAKEFILE) FORCE
	cd libxbn/ && $(MAKE) -f $(MAKEFILE) clean
sub-libxbn-distclean: libxbn/$(MAKEFILE) FORCE
	cd libxbn/ && $(MAKE) -f $(MAKEFILE) distclean
sub-libxbn-install_subtargets: libxbn/$(MAKEFILE) FORCE
	cd libxbn/ && $(MAKE) -f $(MAKEFILE) install
sub-libxbn-uninstall_subtargets: libxbn/$(MAKEFILE) FORCE
	cd libxbn/ && $(MAKE) -f $(MAKEFILE) uninstall
testxbn/$(MAKEFILE): 
	@$(CHK_DIR_EXISTS) testxbn/ || $(MKDIR) testxbn/ 
	cd testxbn/ && $(QMAKE) /home/kraus/workspace/xbn/testxbn/testxbn.pro -spec /usr/share/qt/mkspecs/linux-g++ -o $(MAKEFILE)
sub-testxbn-qmake_all:  FORCE
	@$(CHK_DIR_EXISTS) testxbn/ || $(MKDIR) testxbn/ 
	cd testxbn/ && $(QMAKE) /home/kraus/workspace/xbn/testxbn/testxbn.pro -spec /usr/share/qt/mkspecs/linux-g++ -o $(MAKEFILE)
sub-testxbn: testxbn/$(MAKEFILE) sub-libxbn FORCE
	cd testxbn/ && $(MAKE) -f $(MAKEFILE)
sub-testxbn-make_default: testxbn/$(MAKEFILE) sub-libxbn-make_default FORCE
	cd testxbn/ && $(MAKE) -f $(MAKEFILE) 
sub-testxbn-make_first: testxbn/$(MAKEFILE) sub-libxbn-make_first FORCE
	cd testxbn/ && $(MAKE) -f $(MAKEFILE) first
sub-testxbn-all: testxbn/$(MAKEFILE) sub-libxbn-all FORCE
	cd testxbn/ && $(MAKE) -f $(MAKEFILE) all
sub-testxbn-clean: testxbn/$(MAKEFILE) sub-libxbn-clean FORCE
	cd testxbn/ && $(MAKE) -f $(MAKEFILE) clean
sub-testxbn-distclean: testxbn/$(MAKEFILE) sub-libxbn-distclean FORCE
	cd testxbn/ && $(MAKE) -f $(MAKEFILE) distclean
sub-testxbn-install_subtargets: testxbn/$(MAKEFILE) sub-libxbn-install_subtargets FORCE
	cd testxbn/ && $(MAKE) -f $(MAKEFILE) install
sub-testxbn-uninstall_subtargets: testxbn/$(MAKEFILE) sub-libxbn-uninstall_subtargets FORCE
	cd testxbn/ && $(MAKE) -f $(MAKEFILE) uninstall
xsltp/$(MAKEFILE): 
	@$(CHK_DIR_EXISTS) xsltp/ || $(MKDIR) xsltp/ 
	cd xsltp/ && $(QMAKE) /home/kraus/workspace/xbn/xsltp/xsltp.pro -spec /usr/share/qt/mkspecs/linux-g++ -o $(MAKEFILE)
sub-xsltp-qmake_all:  FORCE
	@$(CHK_DIR_EXISTS) xsltp/ || $(MKDIR) xsltp/ 
	cd xsltp/ && $(QMAKE) /home/kraus/workspace/xbn/xsltp/xsltp.pro -spec /usr/share/qt/mkspecs/linux-g++ -o $(MAKEFILE)
sub-xsltp: xsltp/$(MAKEFILE) sub-libxbn FORCE
	cd xsltp/ && $(MAKE) -f $(MAKEFILE)
sub-xsltp-make_default: xsltp/$(MAKEFILE) sub-libxbn-make_default FORCE
	cd xsltp/ && $(MAKE) -f $(MAKEFILE) 
sub-xsltp-make_first: xsltp/$(MAKEFILE) sub-libxbn-make_first FORCE
	cd xsltp/ && $(MAKE) -f $(MAKEFILE) first
sub-xsltp-all: xsltp/$(MAKEFILE) sub-libxbn-all FORCE
	cd xsltp/ && $(MAKE) -f $(MAKEFILE) all
sub-xsltp-clean: xsltp/$(MAKEFILE) sub-libxbn-clean FORCE
	cd xsltp/ && $(MAKE) -f $(MAKEFILE) clean
sub-xsltp-distclean: xsltp/$(MAKEFILE) sub-libxbn-distclean FORCE
	cd xsltp/ && $(MAKE) -f $(MAKEFILE) distclean
sub-xsltp-install_subtargets: xsltp/$(MAKEFILE) sub-libxbn-install_subtargets FORCE
	cd xsltp/ && $(MAKE) -f $(MAKEFILE) install
sub-xsltp-uninstall_subtargets: xsltp/$(MAKEFILE) sub-libxbn-uninstall_subtargets FORCE
	cd xsltp/ && $(MAKE) -f $(MAKEFILE) uninstall
xpath/$(MAKEFILE): 
	@$(CHK_DIR_EXISTS) xpath/ || $(MKDIR) xpath/ 
	cd xpath/ && $(QMAKE) /home/kraus/workspace/xbn/xpath/xpath.pro -spec /usr/share/qt/mkspecs/linux-g++ -o $(MAKEFILE)
sub-xpath-qmake_all:  FORCE
	@$(CHK_DIR_EXISTS) xpath/ || $(MKDIR) xpath/ 
	cd xpath/ && $(QMAKE) /home/kraus/workspace/xbn/xpath/xpath.pro -spec /usr/share/qt/mkspecs/linux-g++ -o $(MAKEFILE)
sub-xpath: xpath/$(MAKEFILE) sub-libxbn FORCE
	cd xpath/ && $(MAKE) -f $(MAKEFILE)
sub-xpath-make_default: xpath/$(MAKEFILE) sub-libxbn-make_default FORCE
	cd xpath/ && $(MAKE) -f $(MAKEFILE) 
sub-xpath-make_first: xpath/$(MAKEFILE) sub-libxbn-make_first FORCE
	cd xpath/ && $(MAKE) -f $(MAKEFILE) first
sub-xpath-all: xpath/$(MAKEFILE) sub-libxbn-all FORCE
	cd xpath/ && $(MAKE) -f $(MAKEFILE) all
sub-xpath-clean: xpath/$(MAKEFILE) sub-libxbn-clean FORCE
	cd xpath/ && $(MAKE) -f $(MAKEFILE) clean
sub-xpath-distclean: xpath/$(MAKEFILE) sub-libxbn-distclean FORCE
	cd xpath/ && $(MAKE) -f $(MAKEFILE) distclean
sub-xpath-install_subtargets: xpath/$(MAKEFILE) sub-libxbn-install_subtargets FORCE
	cd xpath/ && $(MAKE) -f $(MAKEFILE) install
sub-xpath-uninstall_subtargets: xpath/$(MAKEFILE) sub-libxbn-uninstall_subtargets FORCE
	cd xpath/ && $(MAKE) -f $(MAKEFILE) uninstall
xmlos/$(MAKEFILE): 
	@$(CHK_DIR_EXISTS) xmlos/ || $(MKDIR) xmlos/ 
	cd xmlos/ && $(QMAKE) /home/kraus/workspace/xbn/xmlos/xmlos.pro -spec /usr/share/qt/mkspecs/linux-g++ -o $(MAKEFILE)
sub-xmlos-qmake_all:  FORCE
	@$(CHK_DIR_EXISTS) xmlos/ || $(MKDIR) xmlos/ 
	cd xmlos/ && $(QMAKE) /home/kraus/workspace/xbn/xmlos/xmlos.pro -spec /usr/share/qt/mkspecs/linux-g++ -o $(MAKEFILE)
sub-xmlos: xmlos/$(MAKEFILE) sub-libxbn FORCE
	cd xmlos/ && $(MAKE) -f $(MAKEFILE)
sub-xmlos-make_default: xmlos/$(MAKEFILE) sub-libxbn-make_default FORCE
	cd xmlos/ && $(MAKE) -f $(MAKEFILE) 
sub-xmlos-make_first: xmlos/$(MAKEFILE) sub-libxbn-make_first FORCE
	cd xmlos/ && $(MAKE) -f $(MAKEFILE) first
sub-xmlos-all: xmlos/$(MAKEFILE) sub-libxbn-all FORCE
	cd xmlos/ && $(MAKE) -f $(MAKEFILE) all
sub-xmlos-clean: xmlos/$(MAKEFILE) sub-libxbn-clean FORCE
	cd xmlos/ && $(MAKE) -f $(MAKEFILE) clean
sub-xmlos-distclean: xmlos/$(MAKEFILE) sub-libxbn-distclean FORCE
	cd xmlos/ && $(MAKE) -f $(MAKEFILE) distclean
sub-xmlos-install_subtargets: xmlos/$(MAKEFILE) sub-libxbn-install_subtargets FORCE
	cd xmlos/ && $(MAKE) -f $(MAKEFILE) install
sub-xmlos-uninstall_subtargets: xmlos/$(MAKEFILE) sub-libxbn-uninstall_subtargets FORCE
	cd xmlos/ && $(MAKE) -f $(MAKEFILE) uninstall

Makefile: xbn.pro  /usr/share/qt/mkspecs/linux-g++/qmake.conf /usr/share/qt/mkspecs/common/unix.conf \
		/usr/share/qt/mkspecs/common/linux.conf \
		/usr/share/qt/mkspecs/common/gcc-base.conf \
		/usr/share/qt/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt/mkspecs/common/g++-base.conf \
		/usr/share/qt/mkspecs/common/g++-unix.conf \
		/usr/share/qt/mkspecs/qconfig.pri \
		/usr/share/qt/mkspecs/modules/qt_phonon.pri \
		/usr/share/qt/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt/mkspecs/features/qt_functions.prf \
		/usr/share/qt/mkspecs/features/qt_config.prf \
		/usr/share/qt/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt/mkspecs/features/default_pre.prf \
		/usr/share/qt/mkspecs/features/release.prf \
		/usr/share/qt/mkspecs/features/default_post.prf \
		/usr/share/qt/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt/mkspecs/features/warn_on.prf \
		/usr/share/qt/mkspecs/features/qt.prf \
		/usr/share/qt/mkspecs/features/unix/thread.prf \
		/usr/share/qt/mkspecs/features/moc.prf \
		/usr/share/qt/mkspecs/features/resources.prf \
		/usr/share/qt/mkspecs/features/uic.prf \
		/usr/share/qt/mkspecs/features/yacc.prf \
		/usr/share/qt/mkspecs/features/lex.prf \
		/usr/share/qt/mkspecs/features/include_source_dir.prf
	$(QMAKE) -spec /usr/share/qt/mkspecs/linux-g++ -o Makefile xbn.pro
/usr/share/qt/mkspecs/common/unix.conf:
/usr/share/qt/mkspecs/common/linux.conf:
/usr/share/qt/mkspecs/common/gcc-base.conf:
/usr/share/qt/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt/mkspecs/common/g++-base.conf:
/usr/share/qt/mkspecs/common/g++-unix.conf:
/usr/share/qt/mkspecs/qconfig.pri:
/usr/share/qt/mkspecs/modules/qt_phonon.pri:
/usr/share/qt/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt/mkspecs/features/qt_functions.prf:
/usr/share/qt/mkspecs/features/qt_config.prf:
/usr/share/qt/mkspecs/features/exclusive_builds.prf:
/usr/share/qt/mkspecs/features/default_pre.prf:
/usr/share/qt/mkspecs/features/release.prf:
/usr/share/qt/mkspecs/features/default_post.prf:
/usr/share/qt/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt/mkspecs/features/warn_on.prf:
/usr/share/qt/mkspecs/features/qt.prf:
/usr/share/qt/mkspecs/features/unix/thread.prf:
/usr/share/qt/mkspecs/features/moc.prf:
/usr/share/qt/mkspecs/features/resources.prf:
/usr/share/qt/mkspecs/features/uic.prf:
/usr/share/qt/mkspecs/features/yacc.prf:
/usr/share/qt/mkspecs/features/lex.prf:
/usr/share/qt/mkspecs/features/include_source_dir.prf:
qmake: qmake_all FORCE
	@$(QMAKE) -spec /usr/share/qt/mkspecs/linux-g++ -o Makefile xbn.pro

qmake_all: sub-libxbn-qmake_all sub-testxbn-qmake_all sub-xsltp-qmake_all sub-xpath-qmake_all sub-xmlos-qmake_all FORCE

make_default: sub-libxbn-make_default sub-testxbn-make_default sub-xsltp-make_default sub-xpath-make_default sub-xmlos-make_default FORCE
make_first: sub-libxbn-make_first sub-testxbn-make_first sub-xsltp-make_first sub-xpath-make_first sub-xmlos-make_first FORCE
all: sub-libxbn-all sub-testxbn-all sub-xsltp-all sub-xpath-all sub-xmlos-all FORCE
clean: sub-libxbn-clean sub-testxbn-clean sub-xsltp-clean sub-xpath-clean sub-xmlos-clean FORCE
distclean: sub-libxbn-distclean sub-testxbn-distclean sub-xsltp-distclean sub-xpath-distclean sub-xmlos-distclean FORCE
	-$(DEL_FILE) Makefile
install_subtargets: sub-libxbn-install_subtargets sub-testxbn-install_subtargets sub-xsltp-install_subtargets sub-xpath-install_subtargets sub-xmlos-install_subtargets FORCE
uninstall_subtargets: sub-libxbn-uninstall_subtargets sub-testxbn-uninstall_subtargets sub-xsltp-uninstall_subtargets sub-xpath-uninstall_subtargets sub-xmlos-uninstall_subtargets FORCE

sub-libxbn-check: libxbn/$(MAKEFILE)
	cd libxbn/ && $(MAKE) -f $(MAKEFILE) check
sub-testxbn-check: testxbn/$(MAKEFILE) sub-libxbn-check
	cd testxbn/ && $(MAKE) -f $(MAKEFILE) check
sub-xsltp-check: xsltp/$(MAKEFILE) sub-libxbn-check
	cd xsltp/ && $(MAKE) -f $(MAKEFILE) check
sub-xpath-check: xpath/$(MAKEFILE) sub-libxbn-check
	cd xpath/ && $(MAKE) -f $(MAKEFILE) check
sub-xmlos-check: xmlos/$(MAKEFILE) sub-libxbn-check
	cd xmlos/ && $(MAKE) -f $(MAKEFILE) check
check: sub-libxbn-check sub-testxbn-check sub-xsltp-check sub-xpath-check sub-xmlos-check

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all
install: install_subtargets  FORCE

uninstall:  uninstall_subtargets FORCE

FORCE:

