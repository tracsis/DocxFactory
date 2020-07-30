# DocxFactory compilation instructions
---------------

# Compiling for Windows from WSL
1. Start by installing WSL, and a suitable distro (e.g. Ubuntu 18.04 LTS)
2. Install [the M Cross Environment (MXE)](https://mxe.cc/) and required packages: 
	1. [Install dependencies for MXE](https://mxe.cc/#requirements)
	2. Clone the repo: `git clone https://github.com/mxe/mxe.git`
	3. To install MXE system-wide: 
		```bash
		sudo su
		mv mxe /opt/mxe
		exit
		```
	4. Edit `MXE_TARGETS` in `/opt/mxe/settings.mk` to
		```
		MXE_TARGETS := x86_64-w64-mingw32.shared
		```
	5. Build required packages: 
		```bash
		cd /opt/mxe
		make -j8 cc boost imagemagick minizip zlib xerces icu4c cmake   # DocxFactory dependencies
		```
3. "Install" RapidJSON:
	```bash
	cd ~
	wget https://github.com/Tencent/rapidjson/archive/v1.1.0.tar.gz
	tar xzvf v1.1.0.tar.gz
	cp -r rapidjson-1.1.0/include/rapidjson /opt/mxe/usr/x86_64-w64-mingw32.static/include/rapidjson
	```
4. Build and install Zint: 
	1. [Download Zint 2.8.0 from SourceForge](https://sourceforge.net/projects/zint/files/zint/2.8.0/)
	2. Build and install:
		```bash
		cd /where/you/downloaded/zint
		tar xzvf zint-2.8.0.tar.gz
		cd zint-2.8.0
		mkdir build && cd build
		x86_64-w64-mingw32.static-cmake ..
		cd backend
		make
		sudo make install
		```
5. Install LibreOffice SDK
	Do this from Windows, not WSL
	1. [Download and install LibreOffice and LibreOffice SDK for Windows](https://www.libreoffice.org/download/download/)
	2. Open a PowerShell window as administrator (e.g. by right-clicking the Start button)
	3. `cd` to your LibreOffice install directory (most likely `C:\Program Files\LibreOffice 6.4`)
	4. Follow the steps in [this guide](https://studiofreya.com/2016/10/11/integrating-libreoffice-into-cpp/) to generate header files
	5. Place the generated headers in `[libreoffice folder]\sdk\include_generated`
	6. Copy the `sdk`-folder from LibreOffice into `DocxFactory/libs`
6. Build DocxFactory
	```bash
	git clone https://github.com/Eskildybvik/DocxFactory
	cd DocxFactory
	mkdir build && cd build
	x86_64-w64-mingw32.shared-cmake ..
	make
	```

## Fixing errors when building for Windows from WSL
### ImageMagick failed to build because Theora failed to build
Only the examples appear to be broken, so let's replace them with a minimal C++ program to avoid having to edit the makefile.
```bash
cd /opt/mxe
mkdir buildlocal
cp pkg/libtheora-1.1.1.tar.gz buildlocal/
cd buildlocal
tar xzvf libtheora-1.1.1.tar.gz
cd libtheora-1.1.1/examples/
echo "int main(){return 0;}" > encoder_example.c
echo "int main(){return 0;}" > png2theora.c
cd /opt/mxe
make theora theora_SOURCE_TREE=/opt/mxe/buildlocal/libtheora-1.1.1
make imagemagick
```

### magick/image.h not found
`sudo cp -r /opt/mxe/usr/x86_64-w64-mingw32.shared/include/ImageMagick-7/MagickCore /opt/mxe/usr/x86_64-w64-mingw32.shared/include/ImageMagick-7/magick`

### Xerces failed to build
Open the Xerces makefile: `nano /opt/mxe/src/xerces.mk`
Remove the following lines: 
- `--enable-netaccessor-curl \`
- `--disable-shared \`




# Compiling for Linux
These instructions assume you're running Ubuntu or a derivative.
1. Install dependencies: 
	```bash
	sudo apt install build-essential libboost-dev libmagick++-dev libminizip-dev zlib1g-dev libxerces-c-dev libicu-dev cmake
	```
2. "Install" RapidJSON
	```bash
	wget https://github.com/Tencent/rapidjson/archive/v1.1.0.tar.gz
	tar xzvf v1.1.0.tar.gz
	sudo cp -r rapidjson-1.1.0/include/rapidjson /usr/include/rapidjson
	```
3. Build and install Zint: 
	1. [Download Zint 2.8.0 from SourceForge](https://sourceforge.net/projects/zint/files/zint/2.8.0/)
	2. Build and install:
		```bash
		cd /where/you/downloaded/zint
		tar xzvf zint-2.8.0.tar.gz
		cd zint-2.8.0
		mkdir build && cd build
		cmake ..
		cd backend
		make
		sudo make install
		```
4. Install LibreOffice SDK
	0. If you already have LibreOffice from APT, uninstall it
	1. [Download LibreOffice 6.4 and LibreOffice 6.4 SDK debs](https://www.libreoffice.org/download/download/)
	2. Install LibreOffice: 
		```bash
		tar xzvf LibreOffice_6.4.5_Linux_x86-64_deb.tar.gz
		cd LibreOffice_6.4.5.2_Linux_x86-64_deb/DEBS/
		sudo apt install ./*
		```
	3. Install LibreOffice SDK:
		```bash
		tar xzvf LibreOffice_6.4.5_Linux_x86-64_deb_sdk.tar.gz
		cd LibreOffice_6.4.5.2_Linux_x86-64_deb_sdk/DEBS/
		sudo apt install ./*
		```
	4. Generate headers for LibreOffice SDK: 
		```bash
		cd /opt/libreoffice6.4/
		sudo ./sdk/bin/cppumaker -O ./sdk/include_generated ./program/types.rdb ./program/types/offapi.rdb ./program/types/oovbaapi.rdb
		```
5. Build DocxFactory
	```bash
	git clone https://github.com/Eskildybvik/DocxFactory
	cd DocxFactory
	mkdir build && cd build
	cmake ..
	make
	```