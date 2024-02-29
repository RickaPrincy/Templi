#pragma once

#include <Templi/types.hpp>

namespace Templi
{
	bool generate(String template_path,
		String output_path,
		MapString values,
		VectorString ignored_path = {});

	bool generate_with_templi_config(String template_path, String output_path);

	bool configure(String template_path, VectorString ignored_path = {});

	void get_config_value(String template_path, MapString &values, VectorString &ignored_paths);

}  // namespace Templi
