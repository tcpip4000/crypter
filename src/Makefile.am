bin_PROGRAMS = modaler modalgen

modaler_SOURCES = modaler.c
modaler_CPPFLAGS = -Wall -Wl,--as-needed -I$(top_srcdir)/libcrypter
modaler_LDADD = $(top_srcdir)/libcrypter/libcrypter.la

modalgen_SOURCES = modalgen.c
modalgen_CPPFLAGS = -Wall -Wl,--as-needed -I$(top_srcdir)/libcrypter
modalgen_LDADD = $(top_srcdir)/libcrypter/libcrypter.la
