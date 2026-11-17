#pragma once
// oktypes.h was a near-duplicate of bobtypes.h (same ByteArray, IntArray,
// GFX, SPRITE, RenderOrder, Info). Including both in one translation unit
// redefined every type and broke the build wherever the older Bob* family
// met the newer OK* family. It now forwards to the single definition.
// (Previous contents backed up outside the repo during the unification.)
#include "bobtypes.h"
