#ifndef KPARTITION_GLOBAL_H
#define KPARTITION_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(KPARTITION_LIBRARY)
#  define KPARTITIONSHARED_EXPORT Q_DECL_EXPORT
#else
#  define KPARTITIONSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // KPARTITION_GLOBAL_H