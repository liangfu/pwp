
first: build.xml
	ndk-build
	ant debug

clean: 
	rm -rf apk
	rm -rf libs 
	rm $$(find obj | grep .so)
	rm -rf obj/local/armeabi/objs/cvext
# .	rm build.xml

build.xml:
	android update project -p . -s --target android-10

install:
	adb -d install -r ./apk/CvTracker-debug.apk

