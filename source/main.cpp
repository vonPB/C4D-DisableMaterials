// classic API header files
#include <sstream>
#include "c4d_plugin.h"
#include "disable_materials.hpp"

const char* AUTHOR{ "Philipp Bokatius & Henrik S." };
const unsigned MAJOR_VER{ 1 };
const unsigned MINOR_VER{ 0 };

::Bool PluginStart()
{
	if (!DisableMaterials::register_class())
	{
		ApplicationOutput("Failed to register DisableMaterials command");
		return false;
	}
	if(!EnableMaterials::register_class())
	{
		ApplicationOutput("Failed to register EnableMaterials command");
		return false;
	}

	std::ostringstream str;
	str << "DisableMaterials v" << MAJOR_VER << '.' << MINOR_VER << " by " << AUTHOR;
	ApplicationOutput(str.str().c_str());

	return true;
}

void PluginEnd()
{
	// free resources
}

::Bool PluginMessage(::Int32 id, void* data)
{
	

	return true;
}
