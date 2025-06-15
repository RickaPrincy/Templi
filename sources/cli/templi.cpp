#include <Templi/Templi.hpp>
#include <Templi/TempliConfig.hpp>
#include <Templi/types.hpp>
#include <cpp_inquirer/cpp_inquirer.hpp>
#include <filesystem>
#include <iostream>
#include <memory>
#include <rcli/rcli.hpp>

#include "../lib/fs_utils.hpp"
#include "utils.hpp"

const std::string GIT_SUFFIX = ".git";

namespace Templi
{
	auto make_configure_command() -> std::shared_ptr<rcli::command>
	{
		return std::make_shared<rcli::command>("configure",
			"Configure one template to generate templi.json",
			[](rcli::command *_configure)
			{
				std::string template_path = _configure->get_option_value("template_path");
				if (template_path.empty())
				{
					template_path = cpp_inquirer::text_question::prompt(
						"Template Path", { cpp_inquirer::validator_factory::required() });
				}
				try
				{
					configure(template_path);
					std::cout << "[ DONE ]: \"templi.json\" was generated" << "\n";
				}
				catch (Exception error)
				{
					std::cout << "[ ERROR ]: " << error.what() << "\n";
				}
			});
	}

	auto make_generate_command() -> std::shared_ptr<rcli::command>
	{
		return std::make_shared<rcli::command>("generate",
			"Generate new project with one template",
			[](rcli::command *_generate)
			{
				std::string template_path = _generate->get_option_value("template_path");
				std::string output_path = _generate->get_option_value("output_path");
				std::string scope = _generate->get_option_value("scope");

				if (template_path.empty())
				{
					template_path = cpp_inquirer::text_question::prompt(
						"Template Path", { cpp_inquirer::validator_factory::required() });
				}

				if (output_path.empty())
				{
					output_path = cpp_inquirer::text_question::prompt(
						"Output path", { cpp_inquirer::validator_factory::required() });
				}

				auto is_github_repository = false;
				try
				{
					if (template_path.length() >= GIT_SUFFIX.length())
					{
						// test if the template_path is a git repository
						if (0 == template_path.compare(template_path.length() - GIT_SUFFIX.length(),
									 GIT_SUFFIX.length(),
									 GIT_SUFFIX))
						{
							template_path = clone_template(template_path);
							is_github_repository = true;
						}
					}

					std::string valid_template_path = template_path;
					if (!scope.empty())
					{
						valid_template_path =
							(std::filesystem::path(template_path) / std::filesystem::path(scope))
								.string();
					}

					generate_with_templi_config(valid_template_path,
						output_path,
						[&](const Placeholder &placeholder)
						{
							auto result = get_placeholder_value(_generate, placeholder);
							std::cout << "\n";
							return result;
						});

					if (is_github_repository)
					{
						delete_folder(template_path);
					}
					std::cout << "\n[ DONE ]: Project generated successfully\n";
				}
				catch (Exception error)
				{
					std::cout << "[ ERROR ]: " << error.what() << "\n";
					if (is_github_repository && std::filesystem::exists(template_path))
					{
						delete_folder(template_path);
					}
				}
			});
	}
}  // namespace Templi

auto main(int argc, const char *argv[]) -> int	// NOLINT
{
	// base of the application
	rcli::app templi("Templi",
		"Templi is a tool that simplifies boilerplate creation and usage",
		Templi_VERSION);

	rcli::option template_path_option("-t,--template", "Specify template path", "template_path");

	templi.add_informations(
		{ { "Author", "RickaPrincy" }, { "Github", "<https://github.com/RickaPrincy/Templi>" } });

	const auto configure_command = Templi::make_configure_command();
	const auto generate_command = Templi::make_generate_command();

	configure_command->add_option(&template_path_option);
	generate_command->add_option(&template_path_option);
	generate_command->add_option("-o,--output", "Specify output path", "output_path");
	generate_command->add_option(
		"-s, --scope", "Specify which template in the monorepo to use", "scope");

	templi.add_subcommand(&(*configure_command));
	templi.add_subcommand(&(*generate_command));

	return templi.run(argc, argv);
}
