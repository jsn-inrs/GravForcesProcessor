%module GravForcesProcessor

%{
#include "GravForcesProcessor.h"
#include <spdlog/spdlog.h>
%}

%include <std_string.i>
%include <typemaps.i>

%{
#include <string>
#include <spdlog/spdlog.h>
%}

// Header needed for class GravForcesProcessor
%include "GravForcesProcessor.h"

// Header needed for class spdlog
%include "spdlog/spdlog.h"

// Wrappers for spdlog functions
%include "spdlog/common.h"
%include "spdlog/logger.h"
%include "spdlog/sinks/stdout_color_sinks.h"
%include "spdlog/fmt/ostr.h"