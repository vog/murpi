SUBDIRS = src

bin_PREFIX = /usr

SU	= su -c
EPM	= epm -v -f
ZIP	= zip -r9
NSIS	= makensis-bz2

bindist:
	./configure --prefix=$(bin_PREFIX)
	make
	$(SU) "\
		$(EPM) portable $(PACKAGE) ;\
		$(EPM) rpm $(PACKAGE) ;\
		$(EPM) deb $(PACKAGE)"
