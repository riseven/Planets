// Copyright (C) 2002-2006 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __I_ATTRIBUTE_EXCHANGING_OBJECT_H_INCLUDED__
#define __I_ATTRIBUTE_EXCHANGING_OBJECT_H_INCLUDED__

#include "IUnknown.h"


namespace irr
{

namespace io
{

class IAttributes;

//! Enumation flags passed through SAttributeReadWriteOptions to the IAttributeExchangingObject object
enum E_ATTRIBUTE_READ_WRITE_FLAGS
{
	//! Serialization/Deserializion is done for an xml file
	EARWF_FOR_FILE = 0x00000001,

	//! Serialization/Deserializion is done for an editor property box
	EARWF_FOR_EDITOR = 0x00000002,

	//! When writing filenames, relative paths should be used
	EARWF_USE_RELATIVE_PATHS = 0x00000004
};


//! struct holding data describing options 
struct SAttributeReadWriteOptions
{
	//! constructor
	SAttributeReadWriteOptions()
		: Flags(0), Filename(0)
	{
	}

	//! Combination of E_ATTRIBUTE_READ_WRITE_FLAGS or other, custom ones
	s32 Flags; 

	//! optional filename
	const c8* Filename;
};


//! An object which is able to serialize and deserialize its attributes into an attributes object
class IAttributeExchangingObject : public virtual IUnknown
{
public:

	//! Writes attributes of the object.
	//! Implement this to expose the attributes of your scene node animator for 
	//! scripting languages, editors, debuggers or xml serialization purposes.
	virtual void serializeAttributes(IAttributes* out, io::SAttributeReadWriteOptions* options=0)	{}

	//! Reads attributes of the object.
	//! Implement this to set the attributes of your scene node animator for 
	//! scripting languages, editors, debuggers or xml deserialization purposes.
	virtual void deserializeAttributes(IAttributes* in, SAttributeReadWriteOptions* options=0)	{}

};

} // end namespace io
} // end namespace irr

#endif

