#include "../include/XMLparser.h"
#include <rapidxml/rapidxml_utils.hpp>

void readXMLData(std::ostream &out, const rapidxml::xml_node<> *node, int indent = 0) {
  const auto indentation = std::string(indent * 4, ' ');
  out << indentation.c_str();

  const rapidxml::node_type node_type = node->type();
  switch (node_type) {
  case rapidxml::node_element: {
    out << node->name();
    for (const rapidxml::xml_attribute<> *attribute = node->first_attribute(); attribute;
         attribute = attribute->next_attribute()) {
      out << "" << attribute->name() << ": " << attribute->value() << std::endl;
    }

    for (const rapidxml::xml_node<> *n = node->first_node(); n;
         n = n->next_sibling()) {
      readXMLData(out, n, indent + 1);
    }
    out << std::endl;

  } break;

  case rapidxml::node_data:
    out << node->value() << std::endl;
    break;

  default:
    out << "NODE-TYPE:" << node_type << std::endl;
    break;
  }
}

std::ostream &XMLparser::print(std::ostream &out) const {
  std::string path = "/home/usinglinux/cpp_arvindjangre/3_week/src/";
  std::string file = path + this->m_filename;
  rapidxml::file<> xmlFile(file.c_str());
  rapidxml::xml_document<> doc;
  doc.parse<0>(xmlFile.data());

  readXMLData(out, doc.first_node());
  return out;
}