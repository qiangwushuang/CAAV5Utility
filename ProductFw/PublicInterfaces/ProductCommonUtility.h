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
#include "CATIPrtPart.h"
#include "CATIProduct.h"


class CATIPrtContainer;

class ExportedByProductCommonFw ProductCommonUtility
{
public:
// Standard constructors and destructors
// -------------------------------------
ProductCommonUtility ();
virtual ~ProductCommonUtility ();



//************************************
// Method:     GetPartContainer
// FullName:   ProductCommonUtility::GetPartContainer
// Access:     public static 
// Returns:    HRESULT
// Parameter:  CATIProduct_var ispProduct
// Parameter:  CATIPrtContainer * & oPrtContainer
// Description: 获取Container
//************************************
static HRESULT GetPartContainer(CATIProduct_var ispProduct,CATIPrtContainer *&oPrtContainer);

//************************************
// Method:     GetPrtPart
// FullName:   ProductCommonUtility::GetPrtPart
// Access:     public 
// Returns:    HRESULT
// Parameter:  CATIProduct_var ispProduct
// Parameter:  CATIPrtPart * & oPrtPart
// Description: 获取PrtPart
//************************************
static HRESULT GetPrtPart(CATIProduct_var ispProduct,CATIPrtPart_var ospPrtPart);

//************************************
// Method:     OpenProduct
// FullName:   ProductCommonUtility::OpenProduct
// Access:     public static 
// Returns:    CATIProduct_var
// Parameter:  const CATUnicodeString & iPath
// Description: 打开产品
//************************************
static CATIProduct_var OpenProduct(const CATUnicodeString &iPath);
//************************************
// Method:     GetContainer
// FullName:   ProductCommonUtility::GetContainer
// Access:     public static 
// Returns:    HRESULT
// Parameter:  CATIProduct_var ispProduct
// Parameter:  CATIContainer * & oIContainer
// Description:
//************************************
static HRESULT GetContainer(CATIProduct_var ispProduct,CATIContainer *&oIContainer);
private:
// Copy constructor and equal operator
// -----------------------------------
ProductCommonUtility (ProductCommonUtility &);
ProductCommonUtility& operator=(ProductCommonUtility&);

};

//-----------------------------------------------------------------------

#endif
