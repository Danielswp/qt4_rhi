#ifndef NORMAL_H
#define NORMAL_H

#include <QtCore/qglobal.h>

#ifdef MATH_LIBRARY
#define MATH_EXPORT Q_DECL_EXPORT
#else
#define MATH_EXPORT Q_DECL_IMPORT
#endif

class MATH_EXPORT Normal {
    // 你的类定义，例如：
public:
    Normal();
    int add(int a, int b);
};

#endif
