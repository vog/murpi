SUBDIRS = src
AUTOMAKE_OPTIONS = dist-bzip2

bin_PREFIX = /usr

SU	= su -c
EPM	= epm -v -f
ZIP	= zip -r9
NSIS	= makensis-bz2

bindist:
	make distclean
	./configure --prefix=$(bin_PREFIX)
	make
	$(SU) "\
		$(EPM) portable $(PACKAGE) ;\
		$(EPM) rpm $(PACKAGE) ;\
		$(EPM) deb $(PACKAGE)"
