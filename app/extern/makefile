
VERSION=2.9.5
TARGET=wxWidgets-$(VERSION)

$(TARGET): $(TARGET).tar.bz2
	tar jxvf $(TARGET).tar.bz2
	cd $(TARGET) && ./configure --enable-shared --enable-monolithic --with-opengl --without-regex --without-subdirs --disable-compat28
.PHONY: $(TARGET)

# $(TARGET).tar.bz2:
# 	google-chrome http://sourceforge.net/projects/wxwindows/files/2.9.5/

