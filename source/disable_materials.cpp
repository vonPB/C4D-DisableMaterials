#include "disable_materials.hpp"
#include "c4d_basedocument.h"
#include "c4d_basetag.h"
#include "lib_description.h"
#include "ttexture.h"
#include "c4d_general.h"
#include "c4d_basebitmap.h"


Bool DisableMaterials::Execute(BaseDocument* doc)
{
	AutoAlloc<AtomArray> selecetd_objects;
	AutoAlloc<AtomArray> tags;
	// Get selected objects
	doc->GetActiveObjects(selecetd_objects, GETACTIVEOBJECTFLAGS(1));
	
	for (Int32 i{}; i < selecetd_objects->GetCount(); ++i)
	{
		BaseObject* current_obj{ static_cast<BaseObject*>(selecetd_objects->GetIndex(i)) };
		for (BaseTag* current_tag{ current_obj->GetFirstTag() }; current_tag != nullptr; current_tag = current_tag->GetNext())
		{
			if (current_tag->GetType() != Ttexture)
				continue;

			GeData data;
			current_tag->GetParameter(TEXTURETAG_RESTRICTION, data, DESCFLAGS_GET::NONE);
			if (data.GetString().FindFirst("*disabled*", nullptr))
				continue;

			data.SetString("*disabled*" + data.GetString());
			current_tag->SetParameter(TEXTURETAG_RESTRICTION, data, DESCFLAGS_SET::NONE);
		}
	}
	EventAdd();
	return true;
}

Bool DisableMaterials::register_class()
{
	return RegisterCommandPlugin(ID, "Disable Materials"_s, 0, AutoBitmap("DisableMaterials.tif"_s), "Disable selected materials"_s, new DisableMaterials);
}


Bool EnableMaterials::Execute(BaseDocument* doc)
{
	AutoAlloc<AtomArray> selecetd_objects;
	AutoAlloc<AtomArray> tags;
	// Get selected objects
	doc->GetActiveObjects(selecetd_objects, GETACTIVEOBJECTFLAGS(1));

	for (Int32 i{}; i < selecetd_objects->GetCount(); ++i)
	{
		BaseObject* current_obj{ static_cast<BaseObject*>(selecetd_objects->GetIndex(i)) };
		for (BaseTag* current_tag{ current_obj->GetFirstTag() }; current_tag != nullptr; current_tag = current_tag->GetNext())
		{
			if (current_tag->GetType() != Ttexture)
				continue;

			GeData data;
			current_tag->GetParameter(TEXTURETAG_RESTRICTION, data, DESCFLAGS_GET::NONE);

			Int32 pos{};
			if (!data.GetString().FindFirst("*disabled*", &pos))
				continue;

			if (pos != 0)
				continue;

			auto str{ data.GetString() };
			str.Delete(pos, 10);
			data.SetString(str);
			current_tag->SetParameter(TEXTURETAG_RESTRICTION, data, DESCFLAGS_SET::NONE);
		}
	}
	EventAdd();
	return true;
}

Bool EnableMaterials::register_class()
{
	return RegisterCommandPlugin(ID, "Enable Materials"_s, 0, AutoBitmap("EnableMaterials.tif"_s), "Enable selected materials"_s, new EnableMaterials);
}
