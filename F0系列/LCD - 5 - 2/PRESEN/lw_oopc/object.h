#ifndef __OBJECT_H
#define __OBJECT_H

//�����ʶ��
#define Const             //����
#define Variable          //����
#define Method            //����

//���ʶ������
#define class(c)         struct c

//�����ʶ������
#define object(c,o)      struct c o

//����ָ���ʶ�����壺
#define pobject(c,o)     struct c *o

// ���ܣ�ͨ�õĶ��󴴽���
// ������m��ĳ��Ĵ���������
// 		 o���������Ķ�����
// ���أ���
// ��ע��
#define create(m,o)		m(o)



#endif