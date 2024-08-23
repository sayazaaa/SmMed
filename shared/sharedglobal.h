#ifndef SHAREDGLOBAL_H
#define SHAREDGLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SHARED_LIBRARY)
#  define SHARED_EXPORT Q_DECL_EXPORT
#else
#  define SHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SHAREDGLOBAL_H
