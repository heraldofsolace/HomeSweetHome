//
// Created by aniket on 12/03/2021.
//

#include "template_engine.h"
std::string template_engine::render(std::ifstream &fs) {
  std::string text;
  std::copy(std::istreambuf_iterator<char>(fs), std::istreambuf_iterator<char>(), std::back_inserter(text));
  return render(text);
}
std::string template_engine::render(std::string template_text) {
  return env.render(template_text, data);
}
