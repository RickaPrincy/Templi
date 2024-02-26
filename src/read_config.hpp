#pragma once

#include <Templi/types.hpp>

namespace Templi
{
	void ask_and_get_templi_config_value(String template_path,
		MapString &values,
		VectorString &ignored_paths);
}  // namespace Templi
