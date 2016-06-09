//
// Created by Matthijs on 9-6-2016.
//

#include "gtest/gtest.h"
#include "../source/include/Xml.hpp"

using namespace r2d2::xml;

TEST(Xml, Output) {
    XmlDocument document{"1.0", "", "yes"};
    //document.get_root().add_child(std::unique_ptr<XmlNode>{new XmlNode("Node")});
    document.get_root().add_child(std::unique_ptr<XmlNode>{new XmlNode("Isue")}).add_attribute("line", "10");
    document.get_root().add_child(std::unique_ptr<XmlNode>{new XmlNode("Node")});
    std::cout << document.to_string() << std::endl;
}