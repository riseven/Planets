// Copyright (C) 2002-2006 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in irrlicht.h

#ifndef __I_SCENE_NODE_ANIMATOR_H_INCLUDED__
#define __I_SCENE_NODE_ANIMATOR_H_INCLUDED__

#include "IUnknown.h"
#include "vector3d.h"
#include "ESceneNodeAnimatorTypes.h"
#include "IAttributeExchangingObject.h"

namespace irr
{
namespace io
{
	class IAttributes;
}
namespace scene
{
	class ISceneNode;

	//! Animates a scene node. Can animate position, rotation, material, and so on.
	/** A scene node animator is able to animate a scene node in a very simple way. It may
	change its position, rotation, scale and/or material. There are lots of animators
	to choose from. You can create scene node animators with the ISceneManager interface.
	*/
	class ISceneNodeAnimator : public io::IAttributeExchangingObject
	{
	public:

		//! destructor
		virtual ~ISceneNodeAnimator() {}

		/// <summary>
		/// Animates a scene node.
		/// </summary>
		/// \param node: Node to animate.
		/// \param timeMs: Current time in milli seconds.
		virtual void animateNode(ISceneNode* node, u32 timeMs) = 0;

		//! Returns type of the scene node animator
		virtual ESCENE_NODE_ANIMATOR_TYPE getType()
		{
			return ESNAT_UNKNOWN;
		}
	};
} // end namespace scene
} // end namespace irr

#endif

