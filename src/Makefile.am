MAINTAINERCLEANFILES = Makefile.in Makefile

bin_PROGRAMS = elm_demo_tizen_mobile
elm_demo_tizen_mobile_SOURCES = main.c main.h util.c util.h\
                            bg.c \
                            button.c \
                            checkbox.c \
                            colorselector.c \
                            ctxpopup.c \
                            datetime.c \
                            entry.c \
                            gengrid.c \
                            genlist.c \
                            index.c \
                            label.c \
                            hoversel.c \
                            layout.c \
                            multibuttonentry.c \
                            panel.c \
                            popup.c \
                            progressbar.c \
                            radio.c \
                            scroller.c \
                            slider.c \
                            spinner.c \
                            toolbar.c \
                            tooltip.c
elm_demo_tizen_mobile_CFLAGS = $(ELEMENTARY_CFLAGS) $(CAPIFW_CFLAGS) $(EFLEXTENSION_CFLAGS) -ggdb \
                            -DDATA_DIR='"${prefix}/data/edc/"' \
                            -DEDJE_PATH='"/usr/share/elementary/themes"' \
                            -DIMAGE_DIR='"${prefix}/data/images/"' -I../lib -I../
elm_demo_tizen_mobile_LDADD = $(ELEMENTARY_LIBS) $(CAPIFW_LIBS) $(EFLEXTENSION_LIBS) -lutil -ldl
