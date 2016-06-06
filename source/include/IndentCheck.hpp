//
// Created by Matthijs on 6-6-2016.
//

#ifndef FAGAN_INDENTCHECK_HPP
#define FAGAN_INDENTCHECK_HPP
#include "BaseTest.hpp"
namespace r2d2 {
    class IndentCheck : BaseTest {
    private:
        std::string style;

    public:
        IndentCheck(XmlFileFormat & xml);

        void set_indent_style(const std::string & style);

        bool inspect(const std::string &file_contents) override;

        bool inspect_and_fix(std::string &file_contents) override;
    };
}

#endif //FAGAN_INDENTCHECK_HPP
