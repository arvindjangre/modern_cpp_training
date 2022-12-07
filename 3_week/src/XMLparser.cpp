#include "../include/XMLparser.h"
#include <rapidxml/rapidxml_utils.hpp>

void walk(std::ostream &out, const rapidxml::xml_node<> *node, int indent = 0) {
  const auto ind = std::string(indent * 4, ' ');
  out << ind.c_str();

  const rapidxml::node_type t = node->type();
  switch (t) {
  case rapidxml::node_element: {
    out << node->name();
    for (const rapidxml::xml_attribute<> *a = node->first_attribute(); a;
         a = a->next_attribute()) {
      out << "" << a->name() << ": " << a->value() << std::endl;
    }

    for (const rapidxml::xml_node<> *n = node->first_node(); n;
         n = n->next_sibling()) {
      walk(out, n, indent + 1);
    }
    out << std::endl;

  } break;

  case rapidxml::node_data:
    out << node->value() << std::endl;
    break;

  default:
    out << "NODE-TYPE:" << t << std::endl;
    break;
  }
}

std::ostream &XMLparser::print(std::ostream &out) const {
  rapidxml::file<> xmlFile(
      "/home/usinglinux/cpp_arvindjangre/3_week/src/example1.xml");
  rapidxml::xml_document<> doc;
  doc.parse<0>(xmlFile.data());

  walk(out, doc.first_node());
  return out;
}