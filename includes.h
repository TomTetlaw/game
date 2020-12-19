#ifndef INCLUDES_H
#define INCLUDES_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>

#ifdef _WINDOWS
#include <windows.h>
#endif

#include "include/glew.h"

#include "include/stb_image.h"
#include "include/stb_truetype.h"
#include "include/sdl2/sdl.h"

#include "mathlib.h"
#include "utils.h"
#include "array.h"
#include "render.h"
#include "texture.h"
#include "font.h"
#include "hotload.h"
#include "entity.h"
#include "entity_types.h"

#endif
