
//===================================================================
// COPYRIGHT  2020/01/06
//===================================================================
// TreeDbNotify.cpp
// Header definition of class TreeDbNotify
//===================================================================
//
// Usage notes:
//
//===================================================================
//  2020/01/06 Creation: Code generated by the 3DS wizard
//===================================================================

#ifndef TreeDbNotify_H
#define TreeDbNotify_H

#include "CATNotification.h"

//-----------------------------------------------------------------------

class TreeDbNotify: public CATNotification

{
CATDeclareClass;

public:

// Standard constructors and destructors
// -------------------------------------
TreeDbNotify ();
virtual ~TreeDbNotify ();

//
// TODO: Add your methods for this class here.
//

	//------------------------------------
	//	CATNotification
	//------------------------------------


private:
// Copy constructor and equal operator
// -----------------------------------
TreeDbNotify (TreeDbNotify &);
TreeDbNotify& operator=(TreeDbNotify&);
};

//-----------------------------------------------------------------------

#endif

