# DocxFactory compilation instructions
---------------

# Cross-Compiling for Windows from WSL or Linux
0. Start by installing WSL, and a suitable distro (e.g. Ubuntu 18.04 LTS)
1. Install [the M Cross Environment (MXE)](https://mxe.cc/) and required packages: 
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
		MXE_TARGETS := x86_64-w64-mingw32.static
		```
	5. Build required packages: 
		```bash
		cd /opt/mxe
		make -j8 cc boost imagemagick minizip zlib xerces icu4c cmake   # DocxFactory dependencies
		```
2. "Install" RapidJSON:
	```bash
	cd ~
	wget https://github.com/Tencent/rapidjson/archive/v1.1.0.tar.gz
	tar xzvf v1.1.0.tar.gz
	cp -r rapidjson-1.1.0/include/rapidjson /opt/mxe/usr/x86_64-w64-mingw32.static/include/rapidjson
	```
3. Build and install Zint: 
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
4. Install LibreOffice SDK (coming soon)
5. Build DocxFactory
	```bash
	git clone https://github.com/impetusafea/DocxFactory
	cd DocxFactory
	mkdir build && cd build
	x86_64-w64-mingw32.static-cmake ..
	make
	```
