project(DocxFactory)

cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 11)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")


find_package(PkgConfig REQUIRED)
find_package(ICU REQUIRED i18n io le lx uc)
find_package(Boost REQUIRED)
find_package(ZLIB REQUIRED)
find_package(ImageMagick REQUIRED Magick++)
find_package(PkgConfig REQUIRED)
find_package(XercesC REQUIRED)
pkg_check_modules(MiniZip REQUIRED minizip)
find_package(Zint REQUIRED)

if(NOT LIBREOFFICE_SDK_PATH)
	if(WIN32)
		set(LIBREOFFICE_SDK_PATH ${CMAKE_SOURCE_DIR}/libs/sdk)
	else()
		set(LIBREOFFICE_SDK_PATH "/opt/libreoffice6.4/sdk")	
	endif()
endif(NOT LIBREOFFICE_SDK_PATH)

set(LIBREOFFICE_SDK_INCLUDE_DIRS ${LIBREOFFICE_SDK_PATH}/include_generated ${LIBREOFFICE_SDK_PATH}/include)
set(LIBREOFFICE_SDK_LIB_DIRS ${LIBREOFFICE_SDK_PATH}/lib)
if(WIN32)
	set(LIBREOFFICE_SDK_LIBRARIES
		${LIBREOFFICE_SDK_LIB_DIRS}/icppu.lib
		${LIBREOFFICE_SDK_LIB_DIRS}/icppuhelper.lib
		${LIBREOFFICE_SDK_LIB_DIRS}/isal.lib
		${LIBREOFFICE_SDK_LIB_DIRS}/isalhelper.lib
	)
else()
	set(LIBREOFFICE_SDK_LIBRARIES
		${LIBREOFFICE_SDK_LIB_DIRS}/libuno_cppu.so
		${LIBREOFFICE_SDK_LIB_DIRS}/libuno_cppuhelpergcc3.so
		${LIBREOFFICE_SDK_LIB_DIRS}/libuno_sal.so
		${LIBREOFFICE_SDK_LIB_DIRS}/libuno_salhelpergcc3.so
	)
endif()


include_directories(
	${CMAKE_SOURCE_DIR}/include
	${ICU_INCLUDE_DIRS}
	${BOOST_INCLUDE_DIRS}
	${ZLIB_INCLUDE_DIRS}
	${ImageMagick_INCLUDE_DIRS}
	${ImageMagick_Magick++_INCLUDE_DIRS}
	${XercesC_INCLUDE_DIRS}
	${MiniZip_INCLUDE_DIRS}
	${ZINT_INCLUDE_DIR}
	${LIBREOFFICE_SDK_INCLUDE_DIRS}
)


if(WIN32)
	set(PLATFORM_UTIL ${CMAKE_SOURCE_DIR}/src/win/WinFunc.cpp)
else()
	set(PLATFORM_UTIL ${CMAKE_SOURCE_DIR}/src/unix/UnixFunc.cpp)
endif()
add_library(libDocxFactoryLib STATIC
	${CMAKE_SOURCE_DIR}/src/barcode/BarcodeFunc.cpp

	${CMAKE_SOURCE_DIR}/src/console/ConsoleException.cpp
	${CMAKE_SOURCE_DIR}/src/console/ConsoleUsageException.cpp
	${CMAKE_SOURCE_DIR}/src/console/getopt.c
	${CMAKE_SOURCE_DIR}/src/console/GetOptException.cpp
	${CMAKE_SOURCE_DIR}/src/console/InvalidArgException.cpp
	${CMAKE_SOURCE_DIR}/src/console/InvalidOptException.cpp
	${CMAKE_SOURCE_DIR}/src/console/MissingArgException.cpp
	${CMAKE_SOURCE_DIR}/src/console/MissingOptException.cpp
	${CMAKE_SOURCE_DIR}/src/console/UnexpectedArgException.cpp
	${CMAKE_SOURCE_DIR}/src/console/UnexpectedOptException.cpp

	${CMAKE_SOURCE_DIR}/src/json/JsonException.cpp
	${CMAKE_SOURCE_DIR}/src/json/JsonFunc.cpp
	${CMAKE_SOURCE_DIR}/src/json/ParseJsonException.cpp
	${CMAKE_SOURCE_DIR}/src/json/ParseJsonFileException.cpp

	${CMAKE_SOURCE_DIR}/src/locale/IcuException.cpp
	${CMAKE_SOURCE_DIR}/src/locale/InvalidCodePageException.cpp
	${CMAKE_SOURCE_DIR}/src/locale/InvalidDateFormatException.cpp
	${CMAKE_SOURCE_DIR}/src/locale/InvalidDateTimeStrException.cpp
	${CMAKE_SOURCE_DIR}/src/locale/InvalidFirstWeekDayException.cpp
	${CMAKE_SOURCE_DIR}/src/locale/InvalidYearOffsetException.cpp
	${CMAKE_SOURCE_DIR}/src/locale/LocaleException.cpp
	${CMAKE_SOURCE_DIR}/src/locale/LocaleFunc.cpp

	${CMAKE_SOURCE_DIR}/src/math/MathFunc.cpp

	${CMAKE_SOURCE_DIR}/src/os/DirNotFoundException.cpp
	${CMAKE_SOURCE_DIR}/src/os/FileExistsException.cpp
	${CMAKE_SOURCE_DIR}/src/os/FileNotFoundException.cpp
	${CMAKE_SOURCE_DIR}/src/os/FileNotOpenException.cpp
	${CMAKE_SOURCE_DIR}/src/os/FileNotRemovedException.cpp
	${CMAKE_SOURCE_DIR}/src/os/InvalidFileUrlException.cpp
	${CMAKE_SOURCE_DIR}/src/os/OsException.cpp
	${CMAKE_SOURCE_DIR}/src/os/OsFunc.cpp
	${CMAKE_SOURCE_DIR}/src/os/PathMissingExtException.cpp
	${CMAKE_SOURCE_DIR}/src/os/PathMissingFileException.cpp
	${CMAKE_SOURCE_DIR}/src/os/UnsupportedFileTypeException.cpp

	${CMAKE_SOURCE_DIR}/src/parser/ParserException.cpp
	${CMAKE_SOURCE_DIR}/src/parser/ParserFunc.cpp
	${CMAKE_SOURCE_DIR}/src/parser/UnclosedBracketException.cpp
	${CMAKE_SOURCE_DIR}/src/parser/UnexpectedBracketException.cpp
	${CMAKE_SOURCE_DIR}/src/parser/UnmatchedQuoteException.cpp

	${CMAKE_SOURCE_DIR}/src/str/StrEntries.cpp
	${CMAKE_SOURCE_DIR}/src/str/StrFunc.cpp
	
	${CMAKE_SOURCE_DIR}/src/time/TimeFunc.cpp
	
	${CMAKE_SOURCE_DIR}/src/util/ArgTypeMismatchException.cpp
	${CMAKE_SOURCE_DIR}/src/util/DocxFactoryException.cpp
	${CMAKE_SOURCE_DIR}/src/util/DocxFactoryTimer.cpp
	${CMAKE_SOURCE_DIR}/src/util/GeneralException.cpp
	${CMAKE_SOURCE_DIR}/src/util/UnknownException.cpp

	${CMAKE_SOURCE_DIR}/src/xml/AsciiToXMLCh.cpp
	${CMAKE_SOURCE_DIR}/src/xml/DomException.cpp
	${CMAKE_SOURCE_DIR}/src/xml/InvalidXmlPathException.cpp
	${CMAKE_SOURCE_DIR}/src/xml/NodeNotFoundException.cpp
	${CMAKE_SOURCE_DIR}/src/xml/ParseXmlException.cpp
	${CMAKE_SOURCE_DIR}/src/xml/ParseXmlFileException.cpp
	${CMAKE_SOURCE_DIR}/src/xml/StrToXMLCh.cpp
	${CMAKE_SOURCE_DIR}/src/xml/Utf8ToXMLCh.cpp
	${CMAKE_SOURCE_DIR}/src/xml/XmlException.cpp
	${CMAKE_SOURCE_DIR}/src/xml/XmlFunc.cpp
	${CMAKE_SOURCE_DIR}/src/xml/XmlInitializer.cpp
	${CMAKE_SOURCE_DIR}/src/xml/XmlTreeDriller.cpp

	${CMAKE_SOURCE_DIR}/src/zip/FileInfo.cpp
	${CMAKE_SOURCE_DIR}/src/zip/MinizipException.cpp
	${CMAKE_SOURCE_DIR}/src/zip/UnzipFile.cpp
	${CMAKE_SOURCE_DIR}/src/zip/ZipException.cpp
	${CMAKE_SOURCE_DIR}/src/zip/ZipFile.cpp
	${CMAKE_SOURCE_DIR}/src/zip/ZipFileNotOpenException.cpp
	${CMAKE_SOURCE_DIR}/src/zip/ZipFunc.cpp
	${CMAKE_SOURCE_DIR}/src/zip/ZipStreamNotOpenException.cpp
	${CMAKE_SOURCE_DIR}/src/zip/ZipStreamOpenException.cpp

	${PLATFORM_UTIL}
)
target_link_libraries(libDocxFactoryLib
	${ICU_LIBRARIES}
	${ZLIB_LIBRARIES}
	${ImageMagick_LIBRARIES}
	${ImageMagick_Magick++_LIBRARIES}
	${XercesC_LIBRARIES}
	${MiniZip_LIBRARIES}
	${ZINT_LIBRARIES}
)


add_library(libUnoUtil STATIC
	${CMAKE_SOURCE_DIR}/src/UnoUtil/PropertyMap.cpp
	${CMAKE_SOURCE_DIR}/src/UnoUtil/UnoException.cpp
	${CMAKE_SOURCE_DIR}/src/UnoUtil/UnoUtilImpl.cpp
)
target_link_libraries(libUnoUtil
	libDocxFactoryLib
	${LIBREOFFICE_SDK_LIBRARIES}
)
if(UNIX)
	# This macro was used by the LibreOffice SDK, but wasn't defined by GCC
	target_compile_definitions(libUnoUtil PRIVATE LINUX)
endif()


file(GLOB DOCXMERGER_SRC ${CMAKE_SOURCE_DIR}/src/DocxMerger/*.cpp)
file(GLOB DOCXCOMPILER_SRC ${CMAKE_SOURCE_DIR}/src/DocxCompiler/*.cpp)
add_library(libDocxFactory STATIC
	${CMAKE_SOURCE_DIR}/src/ConverterPrinter/ConversionNotSupportedException.cpp
	${CMAKE_SOURCE_DIR}/src/ConverterPrinter/ConverterPrinter.cpp
	${CMAKE_SOURCE_DIR}/src/ConverterPrinter/ConverterPrinterException.cpp
	${CMAKE_SOURCE_DIR}/src/ConverterPrinter/ExportFormatNotSupportedException.cpp
	${CMAKE_SOURCE_DIR}/src/ConverterPrinter/GradeGroup.cpp
	# ${CMAKE_SOURCE_DIR}/src/ConverterPrinter/MsExcelUtil.cpp
	# ${CMAKE_SOURCE_DIR}/src/ConverterPrinter/MsOfficeUtil.cpp
	# ${CMAKE_SOURCE_DIR}/src/ConverterPrinter/MsWordUtil.cpp
	${CMAKE_SOURCE_DIR}/src/ConverterPrinter/OdfConverterUtil.cpp
	${CMAKE_SOURCE_DIR}/src/ConverterPrinter/OleException.cpp
	${CMAKE_SOURCE_DIR}/src/ConverterPrinter/OpenOfficeUtil.cpp
	${CMAKE_SOURCE_DIR}/src/ConverterPrinter/PrintingNotSupportedException.cpp
	${CMAKE_SOURCE_DIR}/src/ConverterPrinter/UtilFailedException.cpp
	${CMAKE_SOURCE_DIR}/src/ConverterPrinter/UtilNotFoundException.cpp

	${CMAKE_SOURCE_DIR}/src/opc/ContentTypeNotFound.cpp
	${CMAKE_SOURCE_DIR}/src/opc/OpcContentTypes.cpp
	${CMAKE_SOURCE_DIR}/src/opc/OpcException.cpp
	${CMAKE_SOURCE_DIR}/src/opc/OpcFunc.cpp
	${CMAKE_SOURCE_DIR}/src/opc/OpcImageCache.cpp
	${CMAKE_SOURCE_DIR}/src/opc/OpcImageFile.cpp
	${CMAKE_SOURCE_DIR}/src/opc/OpcPackage.cpp
	${CMAKE_SOURCE_DIR}/src/opc/OpcPart.cpp
	${CMAKE_SOURCE_DIR}/src/opc/OpcRelationship.cpp
	${CMAKE_SOURCE_DIR}/src/opc/OpcRelationships.cpp
	${CMAKE_SOURCE_DIR}/src/opc/PartNotFoundException.cpp
	${CMAKE_SOURCE_DIR}/src/opc/PartTypeNotFoundException.cpp

	${DOCXMERGER_SRC}

	${DOCXCOMPILER_SRC}

	${CMAKE_SOURCE_DIR}/src/WordProcessingCompiler/dfwc.cpp
	${CMAKE_SOURCE_DIR}/src/WordProcessingCompiler/WordProcessingCompiler.cpp

	${CMAKE_SOURCE_DIR}/src/WordProcessingMerger/CompileVersionMismatchException.cpp
	${CMAKE_SOURCE_DIR}/src/WordProcessingMerger/dfw.cpp
	${CMAKE_SOURCE_DIR}/src/WordProcessingMerger/InvalidItemNameException.cpp
	${CMAKE_SOURCE_DIR}/src/WordProcessingMerger/InvalidMergeDataException.cpp
	${CMAKE_SOURCE_DIR}/src/WordProcessingMerger/TemplateNotLoadedException.cpp
	${CMAKE_SOURCE_DIR}/src/WordProcessingMerger/WordProcessingException.cpp
	${CMAKE_SOURCE_DIR}/src/WordProcessingMerger/WordProcessingMerger.cpp
	${CMAKE_SOURCE_DIR}/src/WordProcessingMerger/WordProcessingMerger.cpp
) 
target_link_libraries(libDocxFactory
	libDocxFactoryLib
	libUnoUtil
)
if(MSVC)
	target_compile_options(libDocxFactory PRIVATE /permissive)
else()
	target_compile_options(libDocxFactory PRIVATE -fpermissive)
endif()


add_executable(word-processing-compiler
	${CMAKE_SOURCE_DIR}/src/WordProcessingCompiler/word-processing-compiler.cpp
)
target_link_libraries(word-processing-compiler
	libDocxFactory
)
if(CMAKE_DL_LIBS)
	target_link_libraries(word-processing-compiler ${CMAKE_DL_LIBS})
endif(CMAKE_DL_LIBS)


add_executable(word-processing-merger
	${CMAKE_SOURCE_DIR}/src/WordProcessingMerger/word-processing-merger.cpp
)
target_link_libraries(word-processing-merger
	libDocxFactory
)
if(CMAKE_DL_LIBS)
	target_link_libraries(word-processing-merger ${CMAKE_DL_LIBS})
endif(CMAKE_DL_LIBS)
