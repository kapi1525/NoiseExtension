#include <cstdio>
#include <vector>
#include <utility>
#include <string>
#include <string_view>
#include <fstream>
#include <iostream>
#include <regex>

// TODO: rework to not use C++ includes, cause they increase the build time by a lot...
// Especialy regex


// acecalltablegen <input ACECallTable template> <Extension.cpp path> <Extension.hpp path> <output ACECallTable_Macro.cpp>

const char* get_arg(int &argc, char const **&argv) {
    if(argc <= 0) {
        std::fprintf(stderr, "Expected an argument.\n\n");
        std::exit(-1);
    }

    const char* ret = *argv;

    argc--;
    argv = argv + 1;
    return ret;
}

struct func_def {
    std::string return_type;
    std::string name;
    std::vector<std::string> arg_types;
};


const func_def* find_function_by_name(std::string name, const std::vector<func_def>& defs) {
    for (auto &&i : defs) {
        if(i.name == name) {
            return &i;
        }
    }

    return nullptr;
}

std::string get_ace_call_arguments(const func_def* def) {
    std::string ret;

    for (size_t i = 0; i < def->arg_types.size(); i++) {
        ret += "*(" + def->arg_types[i] + " *)&Parameters[" + std::to_string(i) + "]";

        if(i + 1 < def->arg_types.size()) {
            ret += " ,";
        }
    }

    return ret;
}

std::string get_ace_call_arguments2(std::string_view indent, const func_def* def) {
    std::string ret;

    for (size_t i = 0; i < def->arg_types.size(); i++) {
        ret += indent;
        ret += "    long arg" + std::to_string(i) + " = Parameters[" + std::to_string(i) + "];\n";
    }

    return ret;
}

std::string get_ace_call_arguments3(const func_def* def) {
    std::string ret;

    for (size_t i = 0; i < def->arg_types.size(); i++) {
                ret += "*(" + def->arg_types[i] + " *)&arg" + std::to_string(i) + "";

        if(i + 1 < def->arg_types.size()) {
            ret += " ,";
        }
    }

    return ret;
}



int main(int argc, char const *argv[]) {
    (void)get_arg(argc, argv);      // First is the program name

    // Its only a build tool so asume all arguments are fine
    const char* acecalltable_template_path = get_arg(argc, argv);
    const char* extcpp_path = get_arg(argc, argv);
    const char* exthpp_path = get_arg(argc, argv);
    const char* out_path = get_arg(argc, argv);

    // ACE id, function name
    std::vector<std::pair<int, std::string>> linked_conditions;
    std::vector<std::pair<int, std::string>> linked_actions;
    std::vector<std::pair<int, std::string>> linked_expressions;

    // Look for LinkCondition, LinkAction, LinkExpression
    {
        std::regex link_condition_regex("LinkCondition\\( *([0-9]*) *, *([a-zA-Z0-9_]*) *\\);");
        std::regex link_action_regex("LinkAction\\( *([0-9]*) *, *([a-zA-Z0-9_]*) *\\);");
        std::regex link_expression_regex("LinkExpression\\( *([0-9]*) *, *([a-zA-Z0-9_]*) *\\);");

        std::ifstream extcpp(extcpp_path);
        for(std::string line; std::getline(extcpp, line);) {
            if(!extcpp.good()) {
                std::fprintf(stderr, "Failed to read %s\n", extcpp_path);
                return -1;
            }

            std::smatch match;
            if(std::regex_search(line, match, link_condition_regex)) {
                linked_conditions.push_back({std::stoi(match[1]), match[2]});
            }
            if(std::regex_search(line, match, link_action_regex)) {
                linked_actions.push_back({std::stoi(match[1]), match[2]});
            }
            if(std::regex_search(line, match, link_expression_regex)) {
                linked_expressions.push_back({std::stoi(match[1]), match[2]});
            }
        }
    }

    std::vector<func_def> function_definitions;

    // Look for funciton definitions of functions linked earlier
    {
        std::regex function_definition_regex("([a-zA-Z0-9_]+) +([a-zA-Z0-9_]+)\\((.*)\\);");
        std::regex single_argument_regex(" *(.+?)(?:,| *$)");
        std::regex get_argument_type_regex("(.+?) +([a-zA-Z0-9_]+)$");

        std::ifstream exthpp(exthpp_path);
        for(std::string line; std::getline(exthpp, line);) {
            if(!exthpp.good()) {
                std::fprintf(stderr, "Failed to read %s\n", exthpp_path);
                return -1;
            }

            std::smatch match;
            if(!std::regex_search(line, match, function_definition_regex)) {
                continue;
            }

            func_def function = {
                match[1],
                match[2],
                {},
            };

            std::string arguments = match[3];

            for(;;) {
                // get next argument from a list of arguments
                if(!std::regex_search(arguments, match, single_argument_regex)) {
                    break;
                }
                std::string argument = match[1];
                arguments = arguments.substr(match.length());

                // get argument type.
                if(std::regex_search(argument, match, get_argument_type_regex)) {
                    function.arg_types.push_back(match[1]);
                }
            }

            function_definitions.push_back(function);
        }
    }

    // Use the template to create the output
    {
        std::ifstream acecalltable_template(acecalltable_template_path);
        std::ofstream out(out_path);

        if(!acecalltable_template.good() || !out.good()) {
            return -1;
        }

        // out << "// Generated by acecalltablegen.\n";

        std::regex macro_template_conditions("(.*)#error ASM Condition Replacement Macro was not replaced!");
        std::regex macro_template_actions("(.*)#error ASM Action Replacement Macro was not replaced!");
        std::regex macro_template_expressions("(.*)#error ASM Expression Replacement Macro was not replaced!");

        std::smatch match;

        for (std::string line; std::getline(acecalltable_template, line);) {
            if(std::regex_search(line, match, macro_template_conditions)) {
                std::string indent = match[1];

                // TODO: Verify that conditions work the same as expressions.
                for (auto &&i : linked_conditions) {
                    const func_def* def = find_function_by_name(i.second, function_definitions);

                    if(!def) {
                        std::fprintf(stderr, "Couldn't find function definition for: \"%s()\"\n", i.second.c_str());
                        continue;
                    }

                    out << indent << "case " << i.first << ":\n";
                    out << indent << "    *((" << def->return_type << " *)&Result) = ext->" << def->name << "(";
                    out << get_ace_call_arguments(def) << ");\n";
                    out << indent << "    break;\n";
                }

            } else if(std::regex_search(line, match, macro_template_actions)) {
                std::string indent = match[1];

                for (auto &&i : linked_actions) {
                    const func_def* def = find_function_by_name(i.second, function_definitions);

                    if(!def) {
                        std::fprintf(stderr, "Couldn't find function definition for: \"%s()\"\n", i.second.c_str());
                        continue;
                    }

                    out << indent << "case " << i.first << ":\n";
                    out << indent << "    return ext->" << i.second << "(";


                    out << get_ace_call_arguments(def) << "), 0;\n";
                }

            } else if(std::regex_search(line, match, macro_template_expressions)) {
                std::string indent = match[1];

                for (auto &&i : linked_expressions) {
                    const func_def* def = find_function_by_name(i.second, function_definitions);

                    if(!def) {
                        std::fprintf(stderr, "Couldn't find function definition for: \"%s()\"\n", i.second.c_str());
                        continue;
                    }

                    // FIXME: The compiler does something weird when building to wasm with optimizations (-O2, -O3)
                    // instead of loading all parameters from memory it loads only the first one and the rest are set to 0.
                    // but when the params are first saved in a variable and then later casted to the correct type it magicaly works.
                    // old code works fine with msvc so this feels like a compiler bug.
                    // tested with wasi-sdk 27.
                    // TODO: recheck later with a more recent compiler. maybe find a minimal code to reproduce and submit an issue to llvm-project.
                    // TODO: check if this bug happens for actions and conditions.
                    out << indent << "case " << i.first << ": {\n";
                    out << get_ace_call_arguments2(indent, def) << "\n";
                    out << indent << "    *((" << def->return_type << " *)&Result) = ext->" << def->name << "(";
                    out << get_ace_call_arguments3(def) << ");\n";
                    out << indent << "    } break;\n";
                }

            } else {
                out << line << "\n";
            }
        }
    }

    return 0;
}
