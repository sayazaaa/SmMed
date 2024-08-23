#ifndef SHARED_GLOBAL_H
#define SHARED_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SHARED_LIBRARY)
#  define SHARED_EXPORT Q_DECL_EXPORT
#else
#  define SHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SHARED_GLOBAL_H
