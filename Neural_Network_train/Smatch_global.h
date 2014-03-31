#ifndef SMATCH_GLOBAL_H
#define SMATCH_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SMATCH_LIBRARY)
#  define SMATCHSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SMATCHSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SMATCH_GLOBAL_H
