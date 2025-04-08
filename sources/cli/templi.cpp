#include <TColor/TColor.hpp>
#include <Templi/Templi.hpp>
#include <Templi/TempliConfig.hpp>
#include <Templi/types.hpp>
#include <chrono>
#include <filesystem>
#include <random>
#include <rcli/command.hpp>
#include <rcli/input_config.hpp>
#include <rcli/inputs.hpp>
#include <rcli/rcli.hpp>
#include <sstream>

#include "../lib/fs_utils.hpp"

using namespace Templi;
const std::string GIT_SUFFIX = ".git";

static std::string generate_unique_id();
static void clone_template(std::string &template_path);
static std::string ask_input_value(const Key &key);

int main(int argc, const char *argv[])
{
	// base of the application
	rcli::App templi("templi", "Generate a project easily", Templi_VERSION);
	templi.add_informations(
		{ { "Author", "RickaPrincy" }, { "Github", "<https://github.com/RickaPrincy/Templi>" } });

	rcli::InputConfig config;
	config.required(true).clean(true);

	// configure command
	rcli::Option template_path_option("-t,--template", "Specify template path", "template_path");
	rcli::Command configure("configure",
		"Configure one template to generate templi.json",
		[&](rcli::Command *_configure)
		{
			std::string template_path = _configure->get_option_value("template_path");
			if (template_path.empty())
				template_path = rcli::ask_input_value(config.text("Template path"));
			try
			{
				Templi::configure(template_path);
				TColor::write_endl(TColor::B_GREEN, "[ DONE ]: \"templi.json\" was generated");
			}
			catch (Templi::Exception error)
			{
				std::string message = error.what();
				TColor::write_endl(TColor::B_RED, "[ ERROR ]: " + message);
			}
		});

	configure.add_option(&template_path_option);

	// generate command
	rcli::Command generate("generate",
		"Generate new project with one template",
		[&](rcli::Command *_generate)
		{
			std::string template_path = _generate->get_option_value("template_path");
			std::string output_path = _generate->get_option_value("output_path");
			std::string path_suffix = _generate->get_option_value("path_suffix");

			if (template_path.empty())
				template_path = rcli::ask_input_value(config.text("Template path (or github url)"));

			if (output_path.empty())
				output_path = rcli::ask_input_value(config.text("Output path"));

			try
			{
				auto is_github_repository = false;
				if (template_path.length() >= GIT_SUFFIX.length())
				{
					// test if the template_path is a git repository
					if (0 == template_path.compare(template_path.length() - GIT_SUFFIX.length(),
								 GIT_SUFFIX.length(),
								 GIT_SUFFIX))
					{
						clone_template(template_path);
						is_github_repository = true;
					}
				}

				Templi::generate_with_templi_config(
					template_path, output_path, [&](Key key) { return ask_input_value(key); });
				if (is_github_repository)
				{
					Templi::delete_folder(template_path);
				}

				TColor::write_endl(TColor::B_GREEN, "\n[ DONE ]: Project generated successfully");
			}
			catch (Templi::Exception error)
			{
				std::string message = error.what();
				TColor::write_endl(TColor::B_RED, "[ ERROR ]: " + message);
			}
		});

	generate.add_option(&template_path_option);
	generate.add_option("-o,--output", "Specify output path", "output_path");
	generate.add_option(
		"-p, --path-suffix", "Path suffix after template_path if you use monorepo", "path_suffix");

	templi.add_subcommand(&configure);
	templi.add_subcommand(&generate);

	templi.run(argc, argv);
	return 0;
}

/* Just some functions */
static std::string generate_unique_id()
{
	auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
	std::mt19937_64 generator(seed);

	std::uniform_int_distribution<uint64_t> distribution;
	uint64_t randomValue = distribution(generator);
	std::stringstream ss;
	ss << std::hex << randomValue;
	return ss.str();
}

static void clone_template(std::string &template_path)
{
	std::filesystem::path os_temp_path = std::filesystem::temp_directory_path();
	const std::filesystem::path template_temp_path =
		os_temp_path / std::filesystem::path(generate_unique_id());
	const std::string clone_command =
		"git clone " + template_path + " " + template_temp_path.string();

	template_path = template_temp_path.string();

	TColor::write_endl(
		TColor::B_GREEN, std::string("Cloning the template to " + template_path + " ..."));
	std::system(clone_command.c_str());
}

static std::string ask_input_value(const Key &key)
{
	rcli::InputConfig config;

	if (key.m_type == KeyType::SELECT)
		return rcli::ask_value_in_list_as_number(key.m_label, key.m_choices);

	if (key.m_type == KeyType::BOOLEAN)
		return rcli::ask_boolean(key.m_label, key.m_default == "true") ? "true" : "false";

	config.text(key.m_label)
		.default_value(key.m_default)
		.required(key.m_required)
		.clean(key.m_clean);

	return rcli::ask_input_value(config);
}
