#pragma once

#include "c4d_baselist.h"
#include "c4d_basetag.h"
#include "c4d_commanddata.h"

using namespace cinema;

struct DisableMaterials : CommandData
{
	static const Int32 ID{1052974};

	Bool Execute(BaseDocument* doc, GeDialog* parentManager) override;

	static Bool register_class();

private:
	static void disable(BaseTag* tag);
};

struct EnableMaterials : CommandData
{
	static const Int32 ID{1052975};

	Bool Execute(BaseDocument* doc, GeDialog* parentManager) override;

	static Bool register_class();

private:
	static void enable(BaseTag* tag);
};
