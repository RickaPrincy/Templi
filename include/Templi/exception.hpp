#ifndef __TEMPLI_EXCEPTION__
#define __TEMPLI_EXCEPTION__

    #include <stdexcept>
    #include <string> 

    namespace Templi{
        class InvalidConfigNotFound : public std::exception {
            private:
                std::string _key;
            public:
                InvalidConfigNotFound(const std::string& key) : _key(key) {}
                const char* what() const noexcept override {
                    return ("Invalid templi.json, \"" + _key + "\" was not found").c_str();
                }
        };

        class InvalidConfigTypeError: public std::exception {
            private:
                std::string _key, _type;
            public:
                InvalidConfigTypeError(const std::string& key, const std::string type) : _key(key), _type(type) {}
                const char* what() const noexcept override {
                    return ("Invalid templi.json, \"" + _key + "\" must be " + _type).c_str();
                }
        };
    }
#endif