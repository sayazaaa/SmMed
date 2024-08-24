#ifndef DATACLASS_GLOBAL_H
#define DATACLASS_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DATACLASS_LIBRARY)
#define DATACLASS_EXPORT Q_DECL_EXPORT
#else
#define DATACLASS_EXPORT Q_DECL_IMPORT
#endif

#endif // DATACLASS_GLOBAL_H
