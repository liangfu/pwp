
first: libjpeg-v9a.tar.gz libpng-1.6.9.tar.gz
	tar zxvf libjpeg-v9a.tar.gz
	tar zxvf libpng-1.6.9.tar.gz
	cp configure_customized libjpeg-v9a
	cp configure_customized libpng-1.6.9
	cd libjpeg-v9a && ./configure_customized && make && make install && cd ..
	cd libpng-1.6.9 && ./configure_customized && make && make install && cd ..
.PHONY: first

clean:
	cd libjpeg-v9a && make clean && cd ..
	cd libpng-1.6.9 && make clean && cd ..
	rm -rf libjpeg-v9a libpng-1.6.9