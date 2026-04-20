#pragma once

#include <string>
// набор инструментов для строк(обработка и тд)
bool ParenthesisSyntax(std::string val);

std::string DeleteCircumjacentParentheses(std::string val);

std::string DeleteTheBlank(std::string val);

bool CharacterInParentheses(std::string val, suint64 i);
