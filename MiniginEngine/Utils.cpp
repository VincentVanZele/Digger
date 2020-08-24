#include "MiniginPCH.h"
#include "Utils.h"


bool engine::DoRectsOverlap(const Float4& a, const Float4& b)
{
	return
		!(
			(a._x > (b._x + b._z)) ||
			((a._x + a._z) < b._x) ||
			(a._y > (b._y + b._w)) ||
			((a._y + a._z) < b._y)
			);
}

bool engine::IsPointInRect(const Float4& rect, const Float2& pos)
{
	if (pos._x > rect._x)
	{
		if (pos._x < (rect._x + rect._z))
		{
			if (pos._y > rect._y)
			{
				if (pos._y < (rect._y + rect._w))
				{
					return true;
				}
			}
		}
	}
	return false;
}