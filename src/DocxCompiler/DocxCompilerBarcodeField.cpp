
#include "DocxFactory/DocxCompiler/DocxCompilerItemFile.h"
#include "DocxFactory/DocxCompiler/DocxCompilerItem.h"
#include "DocxFactory/DocxCompiler/DocxCompilerField.h"
#include "DocxFactory/DocxCompiler/DocxCompilerBarcodeField.h"

#include "DocxFactory/barcode/BarcodeFormat.h"

#include "DocxFactory/xml/XmlFunc.h"
#include "DocxFactory/xml/XmlTreeDriller.h"
#include "DocxFactory/xml/Utf8ToXMLCh.h"

#include "DocxFactory/zip/ZipFile.h"
#include "DocxFactory/str/StrFunc.h"
#include "DocxFactory/util/DocxFactoryDefs.h"

#include "xercesc/dom/DOM.hpp"

#include "boost/scoped_ptr.hpp"

using namespace DocxFactory;
using namespace std;



DocxCompilerBarcodeField::DocxCompilerBarcodeField(
	DocxCompilerItem*				p_item,
	const string&					p_name,
	const string&					p_format,
	const map<FieldParam, string>*	p_valueByParam,
	xercesc::DOMElement*			p_placeHolderNode )

	: DocxCompilerField (
		p_item,
		TYPE_BARCODE,
		p_name,
		p_format,
		p_valueByParam,
		p_placeHolderNode )
{
} // C'tor

DocxCompilerBarcodeField::~DocxCompilerBarcodeField()
{
} // d'tor



void DocxCompilerBarcodeField::serialize( ZipFile* p_zipFile )
{
	DocxCompilerField::serialize( p_zipFile );

	p_zipFile ->writeNum<int32>	( m_barcodeFormat ->m_symbology );
	p_zipFile ->writeStr		( m_barcodeFormat ->m_symbologyName );
	p_zipFile ->writeNum<int32>	( m_barcodeFormat ->m_option1 );
	p_zipFile ->writeNum<int32>	( m_barcodeFormat ->m_option2 );
	p_zipFile ->writeNum<int32>	( m_barcodeFormat ->m_option3 );
	p_zipFile ->writeNum<int32>	( m_barcodeFormat ->m_inputMode );

	p_zipFile ->writeNum<float>	( m_barcodeFormat ->m_scale );
	p_zipFile ->writeNum<int32>	( m_barcodeFormat ->m_height );
	p_zipFile ->writeNum<int32>	( m_barcodeFormat ->m_showHrt );
	p_zipFile ->writeNum<int32>	( m_barcodeFormat ->m_angle );
	p_zipFile ->writeNum<int32>	( m_barcodeFormat ->m_fontSize );
	p_zipFile ->writeStr		( m_barcodeFormat ->m_font );
	p_zipFile ->writeStr		( m_barcodeFormat ->m_fgcolor );
	p_zipFile ->writeStr		( m_barcodeFormat ->m_bgcolor );
	p_zipFile ->writeNum<int32>	( m_barcodeFormat ->m_whiteSpaceWidth );
	p_zipFile ->writeNum<int32>	( m_barcodeFormat ->m_borderWidth );
	p_zipFile ->writeNum<int32>	( m_barcodeFormat ->m_outputOptions );
} // serialize
