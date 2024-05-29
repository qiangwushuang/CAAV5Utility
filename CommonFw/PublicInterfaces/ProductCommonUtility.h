//===================================================================
// COPYRIGHT devfun 2024/04/01
//===================================================================
// ProductCommonUtility.cpp
// Header definition of class ProductCommonUtility
//===================================================================
//
// Usage notes:
//
//===================================================================
//  2024/04/01 Creation: Code generated by the 3DS wizard
//===================================================================

#ifndef ProductCommonUtility_H
#define ProductCommonUtility_H

#include "ProductCommonFw.h"
#include "CATIProduct.h"


class CATIPrtContainer;

class ExportedByProductCommonFw ProductCommonUtility
{
public:
// Standard constructors and destructors
// -------------------------------------
ProductCommonUtility ();
virtual ~ProductCommonUtility ();



/*
	Role    :
		
	Param	:	
		CATIProduct_var ispProduct : 
		CATIPrtContainer * & oPrtContainer : 
	Return	:   
		HRESULT
	
	Create	:
		liqiang Date : 20220124
*/
static HRESULT GetPartContainer(CATIProduct_var ispProduct,CATIPrtContainer *&oPrtContainer);

static CATIProduct_var OpenProduct(const CATUnicodeString &iPath);
private:
// Copy constructor and equal operator
// -----------------------------------
ProductCommonUtility (ProductCommonUtility &);
ProductCommonUtility& operator=(ProductCommonUtility&);

};

//-----------------------------------------------------------------------

#endif