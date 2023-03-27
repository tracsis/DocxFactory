
#include "DocxFactory/barcode/BarcodeFunc.h"
#include "DocxFactory/barcode/BarcodeFormat.h"

#include "DocxFactory/str/StrFunc.h"

#include <climits>
#include <cstring>

using namespace DocxFactory;
using namespace std;



bool BarcodeFunc::encodeAndPrint(
	BarcodeFormat*	p_barcodeFormat,
	const string&	p_value,
	BarcodePrinter	p_printer,
	string&			p_errTxt,
	string&			p_retVal )
{
	return false;
} // encodeAndPrint
