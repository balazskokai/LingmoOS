#ifndef KCHOICELANGUAGE_GLOBAL_H
#define KCHOICELANGUAGE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(KCHOICELANGUAGE_LIBRARY)
#  define KCHOICELANGUAGESHARED_EXPORT Q_DECL_EXPORT
#else
#  define KCHOICELANGUAGESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // KCHOICELANGUAGE_GLOBAL_H
