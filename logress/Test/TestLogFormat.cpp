/* ---------------------------------------------------------------
 * Copyright (c) Adrian Smith.
 * Licensed under the MIT license. See license.txt at project root.
 * --------------------------------------------------------------- */
#include "Base/Top.h"

#include "Test/TestLogFormat.h"

using Test::LogFormat;

const char LogFormat::kConstructorSymbol = '#';
const char LogFormat::kMethodCallSymbol = '^';
const char LogFormat::kFunctionCallSymbol = '!';
const char LogFormat::kResultSymbol = '=';
const char LogFormat::kObjectIDSymbol = '~';
const char LogFormat::kMethodIndexSymbol = '.';
const char LogFormat::kOpenArgumentListSymbol = '(';
const char LogFormat::kCloseArgumentListSymbol = ')';
