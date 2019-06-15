#pragma once

#include "c4d_baselist.h"
#include "c4d_commanddata.h"


struct DisableMaterials : CommandData
{
	static const Int32 ID{100001};

	Bool Execute(BaseDocument* doc) override;

	static Bool register_class();
};

struct EnableMaterials : CommandData
{
	static const Int32 ID{100002};

	Bool Execute(BaseDocument* doc) override;

	static Bool register_class();
};
