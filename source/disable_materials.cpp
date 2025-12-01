#include "disable_materials.hpp"
#include "c4d_basedocument.h"
#include "lib_description.h"
#include "ttexture.h"
#include "c4d_general.h"
#include "c4d_basebitmap.h"

Bool DisableMaterials::Execute(BaseDocument* doc, GeDialog* parentManager)
{
	AutoAlloc<AtomArray> selected_obj;
	AutoAlloc<AtomArray> selected_tags;

	doc->GetActiveObjects(selected_obj, GETACTIVEOBJECTFLAGS(1));
	doc->GetActiveTags(selected_tags);

	if (selected_obj->GetCount() > 0 && selected_tags->GetCount() > 0)
	{
		for (Int32 i{}; i < selected_obj->GetCount(); ++i)
		{
			BaseObject* current_obj{ static_cast<BaseObject*>(selected_obj->GetIndex(i)) };
			for (BaseTag* current_tag{ current_obj->GetFirstTag() }; current_tag != nullptr; current_tag = current_tag->GetNext())
			{
				for (Int32 j{}; j < selected_tags->GetCount(); ++j)
				{
					if (current_tag == selected_tags->GetIndex(j))
						goto skip_tag;
				}
				disable(current_tag);
			skip_tag:;
			}
		}
	}

	else if (selected_obj->GetCount() != 0)
	{
		for (Int32 i{}; i < selected_obj->GetCount(); ++i)
		{
			BaseObject* current_obj{ static_cast<BaseObject*>(selected_obj->GetIndex(i)) };
			for (BaseTag* current_tag{ current_obj->GetFirstTag() }; current_tag != nullptr; current_tag = current_tag->GetNext())
			{
				disable(current_tag);
			}
		}
	}
	else if(selected_tags->GetCount() != 0){
		for (Int32 i{}; i < selected_tags->GetCount(); ++i)
		{
			auto current_tag{ static_cast<BaseTag*>(selected_tags->GetIndex(i)) };
			disable(current_tag);
		}
	}
	EventAdd();
	return true;
}
Bool DisableMaterials::register_class()
{
	return RegisterCommandPlugin(ID, "Disable Materials"_s, 0, AutoBitmap("DisableMaterials.tif"_s), "Disable selected materials"_s, NewObj(DisableMaterials).GetPointer());
}

void DisableMaterials::disable(BaseTag* tag)
{
	if (tag->GetType() != Ttexture)
		return;

	GeData data;
	tag->GetParameter(ConstDescID(DescLevel(TEXTURETAG_RESTRICTION)), data, DESCFLAGS_GET::NONE);
	if (data.GetString().FindFirst("*disabled*", nullptr))
		return;

	data.SetString("*disabled*" + data.GetString());
	tag->SetParameter(ConstDescID(DescLevel(TEXTURETAG_RESTRICTION)), data, DESCFLAGS_SET::NONE);
}


Bool EnableMaterials::Execute(BaseDocument* doc, GeDialog* parentManager)
{
	AutoAlloc<AtomArray> selected_obj;
	AutoAlloc<AtomArray> selected_tags;
	
	doc->GetActiveObjects(selected_obj, GETACTIVEOBJECTFLAGS(1));
	doc->GetActiveTags(selected_tags);

	if (selected_obj->GetCount() > 0 && selected_tags->GetCount() > 0)
	{
		for (Int32 i{}; i < selected_obj->GetCount(); ++i)
		{
			BaseObject* current_obj{ static_cast<BaseObject*>(selected_obj->GetIndex(i)) };
			for (BaseTag* current_tag{ current_obj->GetFirstTag() }; current_tag != nullptr; current_tag = current_tag->GetNext())
			{
				for (Int32 j{}; j < selected_tags->GetCount(); ++j)
				{
					if (current_tag == selected_tags->GetIndex(j))
						goto skip_tag;
				}
				enable(current_tag);
			skip_tag:;
			}
		}
	}
	else if (selected_obj->GetCount() != 0)
	{
		for (Int32 i{}; i < selected_obj->GetCount(); ++i)
		{
			auto current_obj{ static_cast<BaseObject*>(selected_obj->GetIndex(i)) };
			for (BaseTag* current_tag{ current_obj->GetFirstTag() }; current_tag != nullptr; current_tag = current_tag->GetNext())
			{
				enable(current_tag);
			}
		}
	}
	else if(selected_tags->GetCount() != 0)
	{
		for (Int32 i{}; i < selected_tags->GetCount(); ++i)
		{
			auto current_tag{ static_cast<BaseTag*>(selected_tags->GetIndex(i)) };
			enable(current_tag);
		}
	}
	EventAdd();
	return true;
}
Bool EnableMaterials::register_class()
{
	return RegisterCommandPlugin(ID, "Enable Materials"_s, 0, AutoBitmap("EnableMaterials.tif"_s), "Enable selected materials"_s, NewObj(EnableMaterials).GetPointer());
}

void EnableMaterials::enable(BaseTag* tag)
{
	if (tag->GetType() != Ttexture)
		return;

	GeData data;
	tag->GetParameter(ConstDescID(DescLevel(TEXTURETAG_RESTRICTION)), data, DESCFLAGS_GET::NONE);

	Int32 pos{};
	if (!data.GetString().FindFirst("*disabled*", &pos))
		return;

	if (pos != 0)
		return;

	auto str{ data.GetString() };
	str.Delete(pos, 10);
	data.SetString(str);
    tag->SetParameter(ConstDescID(DescLevel(TEXTURETAG_RESTRICTION)), data, DESCFLAGS_SET::NONE);
}
