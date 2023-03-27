project(DocxFactory)

cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 11)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")


find_package(PkgConfig REQUIRED)
# find_package(ICU COMPONENTS i18n io le lx uc)
pkg_check_modules(ICUi18n REQUIRED icu-i18n)
pkg_check_modules(ICUio REQUIRED icu-io)
pkg_check_modules(ICUuc REQUIRED icu-uc)
find_package(Boost REQUIRED)
find_package(ZLIB REQUIRED)
find_package(ImageMagick REQUIRED Magick++ MagickWand MagickCore)
find_package(XercesC REQUIRED)
pkg_check_modules(MiniZip REQUIRED minizip)


include_directories(
	${CMAKE_SOURCE_DIR}/include
	${CMAKE_SOURCE_DIR}/rapidjson/include
	${ICUi18n_INCLUDE_DIRS}
	${ICUio_INCLUDE_DIRS}
	${ICUuc_INCLUDE_DIRS}
	${BOOST_INCLUDE_DIRS}
	${ZLIB_INCLUDE_DIRS}
	${ImageMagick_INCLUDE_DIRS}
	${ImageMagick_Magick++_INCLUDE_DIRS}
	${ImageMagick_MagickWand_INCLUDE_DIRS}
	${ImageMagick_MagickCore_INCLUDE_DIRS}
	${XercesC_INCLUDE_DIRS}
	${MiniZip_INCLUDE_DIRS}
)


if(WIN32)
	set(PLATFORM_UTIL ${CMAKE_SOURCE_DIR}/src/win/WinFunc.cpp)
else()
	set(PLATFORM_UTIL ${CMAKE_SOURCE_DIR}/src/unix/UnixFunc.cpp)
endif()
add_library(DocxFactoryLib STATIC
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

	${PLATFORM_UTIL}
	
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
)
target_link_libraries(DocxFactoryLib
	${ICUi18n_LIBRARIES}
	${ICUio_LIBRARIES}
	${ICUuc_LIBRARIES}
	${ZLIB_LIBRARIES}
	${ImageMagick_LIBRARIES}
	${ImageMagick_Magick++_LIBRARIES}
	${ImageMagick_MagickCore_LIBRARIES}
	${ImageMagick_MagickWand_LIBRARIES}
	${XercesC_LIBRARIES}
	${MiniZip_LIBRARIES}
)
if(WIN32)
	target_link_libraries(DocxFactoryLib version)
endif(WIN32)


target_link_libraries(
	DocxFactoryLib
)


add_library(DocxFactory SHARED

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

	${CMAKE_SOURCE_DIR}/src/DocxCompiler/DocxCompilerAltChunkField.cpp
	${CMAKE_SOURCE_DIR}/src/DocxCompiler/DocxCompilerChartFieldXYSize.cpp
	${CMAKE_SOURCE_DIR}/src/DocxCompiler/DocxCompilerNumberField.cpp
	${CMAKE_SOURCE_DIR}/src/DocxCompiler/DocxCompilerBarcodeField.cpp
	${CMAKE_SOURCE_DIR}/src/DocxCompiler/DocxCompilerDateTimeField.cpp
	${CMAKE_SOURCE_DIR}/src/DocxCompiler/DocxCompilerPicField.cpp
	${CMAKE_SOURCE_DIR}/src/DocxCompiler/DocxCompilerBookmark.cpp
	${CMAKE_SOURCE_DIR}/src/DocxCompiler/DocxCompilerField.cpp
	${CMAKE_SOURCE_DIR}/src/DocxCompiler/DocxCompilerSettingsFile.cpp
	${CMAKE_SOURCE_DIR}/src/DocxCompiler/DocxCompilerBooleanField.cpp
	${CMAKE_SOURCE_DIR}/src/DocxCompiler/DocxCompilerFile.cpp
	${CMAKE_SOURCE_DIR}/src/DocxCompiler/DocxCompilerStyle.cpp
	${CMAKE_SOURCE_DIR}/src/DocxCompiler/DocxCompilerChartField.cpp
	${CMAKE_SOURCE_DIR}/src/DocxCompiler/DocxCompilerId.cpp
	${CMAKE_SOURCE_DIR}/src/DocxCompiler/DocxCompilerStyleFile.cpp
	${CMAKE_SOURCE_DIR}/src/DocxCompiler/DocxCompilerChartFieldFixedSeries.cpp
	${CMAKE_SOURCE_DIR}/src/DocxCompiler/DocxCompilerItem.cpp
	${CMAKE_SOURCE_DIR}/src/DocxCompiler/DocxCompilerTableStyle.cpp
	${CMAKE_SOURCE_DIR}/src/DocxCompiler/DocxCompilerChartFieldSeries.cpp
	${CMAKE_SOURCE_DIR}/src/DocxCompiler/DocxCompilerItemFile.cpp
	${CMAKE_SOURCE_DIR}/src/DocxCompiler/DocxCompilerTextField.cpp
	${CMAKE_SOURCE_DIR}/src/DocxCompiler/DocxCompilerChartFieldSingleSeries.cpp
	${CMAKE_SOURCE_DIR}/src/DocxCompiler/DocxCompilerItemGroup.cpp
	${CMAKE_SOURCE_DIR}/src/DocxCompiler/DocxCompilerXmlString.cpp
	${CMAKE_SOURCE_DIR}/src/DocxCompiler/DocxCompilerChartFieldXY.cpp
	${CMAKE_SOURCE_DIR}/src/DocxCompiler/DocxCompilerItemLayout.cpp

	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerAltChunkField.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerPasteBarcodeField.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerBarcodeField.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerPasteBooleanField.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerBooleanField.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerPasteChartAxis.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerChartAxis.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerPasteChartAxisDateTime.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerChartAxisDateTime.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerPasteChartAxisNumber.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerChartAxisNumber.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerPasteChartAxisText.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerChartAxisText.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerPasteChartField.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerChartField.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerPasteChartFieldFixedSeries.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerChartFieldFixedSeries.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerPasteChartFieldSeries.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerChartFieldSeries.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerPasteChartFieldSingleSeries.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerChartFieldSingleSeries.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerPasteChartFieldXY.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerChartFieldXY.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerPasteChartFieldXYSize.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerChartFieldXYSize.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerPasteChartValues.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerChartValues.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerPasteDateTimeField.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerDateTimeField.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerPasteField.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerException.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerPasteFieldGroup.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerField.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerPasteItem.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerFile.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerPasteItemGroup.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerId.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerPasteNumberField.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerItem.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerPastePicField.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerItemFile.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerPasteTextField.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerItemGroup.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerPicField.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerItemLayout.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerSettingsFile.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerNumberField.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerTextField.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerPasteAltChunkField.cpp
	${CMAKE_SOURCE_DIR}/src/DocxMerger/DocxMergerXmlString.cpp

	${CMAKE_SOURCE_DIR}/src/WordProcessingCompiler/dfwc.cpp
	
	${CMAKE_SOURCE_DIR}/src/WordProcessingMerger/CompileVersionMismatchException.cpp
	${CMAKE_SOURCE_DIR}/src/WordProcessingMerger/dfw.cpp
	${CMAKE_SOURCE_DIR}/src/WordProcessingMerger/InvalidItemNameException.cpp
	${CMAKE_SOURCE_DIR}/src/WordProcessingMerger/InvalidMergeDataException.cpp
	${CMAKE_SOURCE_DIR}/src/WordProcessingMerger/TemplateNotLoadedException.cpp
	${CMAKE_SOURCE_DIR}/src/WordProcessingMerger/WordProcessingException.cpp	
)
target_link_libraries(DocxFactory
	DocxFactoryLib
)
if(MSVC)
	target_compile_options(DocxFactory PRIVATE /permissive)
else()
	target_compile_options(DocxFactory PRIVATE -fpermissive)
endif()
if(CMAKE_DL_LIBS)
	target_link_libraries(DocxFactory ${CMAKE_DL_LIBS})
endif(CMAKE_DL_LIBS)


add_executable(word-processing-compiler
	${CMAKE_SOURCE_DIR}/src/WordProcessingCompiler/word-processing-compiler.cpp
	${CMAKE_SOURCE_DIR}/src/WordProcessingCompiler/WordProcessingCompiler.cpp
)
target_link_libraries(word-processing-compiler
	DocxFactory
)
if(CMAKE_DL_LIBS)
	target_link_libraries(word-processing-compiler ${CMAKE_DL_LIBS})
endif(CMAKE_DL_LIBS)


add_executable(word-processing-merger
	${CMAKE_SOURCE_DIR}/src/WordProcessingMerger/word-processing-merger.cpp
	${CMAKE_SOURCE_DIR}/src/WordProcessingMerger/WordProcessingMerger.cpp
)
target_link_libraries(word-processing-merger
	DocxFactory
)
if(CMAKE_DL_LIBS)
	target_link_libraries(word-processing-merger ${CMAKE_DL_LIBS})
endif(CMAKE_DL_LIBS)
