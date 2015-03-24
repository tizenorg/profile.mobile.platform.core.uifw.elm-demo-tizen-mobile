EDJE_FLAGS = \
-id $(top_srcdir)/data/images/ \
-fd $(top_srcdir)/data/fonts/
TARGET = layout.edj button.edj
all: $(TARGET)
$(TARGET):
	edje_cc layout.edc $(EDJE_FLAGS)
	edje_cc button.edc $(EDJE_FLAGS)
install:
	mkdir -p $(DESTDIR)$(prefix)/data/edc
	$(INSTALL) $(TARGET) $(DESTDIR)$(prefix)/data/edc
clean:
	rm -rf *.edj

