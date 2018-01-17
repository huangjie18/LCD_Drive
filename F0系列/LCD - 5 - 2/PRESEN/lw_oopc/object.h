#ifndef __OBJECT_H
#define __OBJECT_H

//分类标识符
#define Const             //常量
#define Variable          //变量
#define Method            //方法

//类标识符定义
#define class(c)         struct c

//对象标识符定义
#define object(c,o)      struct c o

//对象指针标识符定义：
#define pobject(c,o)     struct c *o

// 功能：通用的对象创建宏
// 参数：m，某类的创建函数名
// 		 o，待创建的对象名
// 返回：无
// 备注：
#define create(m,o)		m(o)



#endif