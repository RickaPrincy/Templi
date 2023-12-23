#ifndef __TEMPLI_FS_UTILS__
#define __TEMPLI_FS_UTILS__
    
    #include <fstream>
    #include <functional>
    #include <Templi/parser.hpp>
    #include <Templi/types.hpp>
    
    namespace Templi{
        bool save_file(String path, String text);
        bool save_file(String path, json text);
        bool delete_file(String path);
        bool write_in_open_file(std::ofstream *file,String &text);
        bool copy_folder(String source, String destination);
        void get_folder_files(String path, VectorString &result, VectorString exclude_path= {});
        bool process_for_each_line(String path, std::function<void(const String &line_content)> process);
        
        template <typename T>
        void save_iterator(String path, T &values, String separator = ""){
            String file_content = "";
            for(const auto value: values){
                file_content += value + separator;
            }
            save_file(path, file_content);
        }
    }
#endif