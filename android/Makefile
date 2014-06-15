
debug: build.xml
	ndk-build
	ant debug

release: build.xml release.keystore
	ndk-build
	ant release

clean: 
	rm -rf apk
	rm -rf libs 
	rm -f $$(find obj | grep .so)
	rm -rf obj/local/armeabi/objs/cvext
	rm -f build.xml
	rm -rf gen

build.xml:
	android update project -p . -s --target android-10 --name CompVis

install:
	adb -d install -r ./apk/CompVis-debug.apk

release.keystore:
	keytool -genkey -v -keystore release.keystore -alias releasekey -keyalg RSA -keysize 2048 -validity 30
	jarsigner -verbose -keystore release.keystore apk/CompVis-release-unsigned.apk releasekey

