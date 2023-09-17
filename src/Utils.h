//
// Created by Diego on 16/09/2023.
//

#ifndef OPENGL_UTILS_H
#define OPENGL_UTILS_H

#include <csignal>

#ifdef SIGTRAP
#define _break() raise(SIGTRAP)
#else
#define _break() raise(SIGABRT)
#endif

#endif //OPENGL_UTILS_H
