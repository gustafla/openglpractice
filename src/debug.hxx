#pragma once

#include <string>

#define STRING2(x) #x
#define STRING(x) STRING2(x)

void die(std::string const &msg);
void msg(std::string const &msg);
void chk(std::string const &msg, int n);
void chk(std::string const &msg);
void chk();
