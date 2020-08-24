#pragma once
#include "Structs.h"

namespace engine
{
	// Cannot put body and definition in a same header file
	//  1 > CollisionManager.obj : error LNK2005 : "bool __cdecl engine::DoRectsOverlap(struct engine::Float4 const &,struct engine::Float4 const &)" (? DoRectsOverlap@engine@@YA_NAEBUFloat4@1@0@Z) already defined in ButtonComponent.obj
	//	1 > CollisionManager.obj : error LNK2005 : "bool __cdecl engine::IsPointInRect(struct engine::Float4 const &,struct engine::Float2 const &)" (? IsPointInRect@engine@@YA_NAEBUFloat4@1@AEBUFloat2@1@@Z) already defined in ButtonComponent.obj
	//	1 > Creating library D : \School\2019 - 2020\Prog 4\Minigin\2DAE01_Prog4_05_Van_Zele_Vincent\x64\Debug\Minigin.lib and object D : \School\2019 - 2020\Prog 4\Minigin\2DAE01_Prog4_05_Van_Zele_Vincent\x64\Debug\Minigin.exp
	//	1 > D:\School\2019 - 2020\Prog 4\Minigin\2DAE01_Prog4_05_Van_Zele_Vincent\x64\Debug\Minigin.exe : fatal error LNK1169 : one or more multiply defined symbols found
	
	bool DoRectsOverlap(const Float4& a, const Float4& b);
	bool IsPointInRect(const Float4& rect, const Float2& pos);

}