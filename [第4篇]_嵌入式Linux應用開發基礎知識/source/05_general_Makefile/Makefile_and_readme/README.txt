�������Makefile�֞�3�:
1. 플�Ŀ䛵�Makefile
2. 플�Ŀ䛵�Makefile.build
3. ������Ŀ䛵�Makefile

һ��������Ŀ䛵�Makefile��
   ����Σ���ʽ���£�

EXTRA_CFLAGS  := 
CFLAGS_file.o := 

obj-y += file.o
obj-y += subdir/
   
   "obj-y += file.o"  ��ʾ�Ѯ�ǰĿ��µ�file.c���M�����e��
   "obj-y += subdir/" ��ʾҪ�M��subdir�@����Ŀ���ȥ�����ļ����M�����e������Щ�ļ���subdirĿ��µ�Makefile�Q����
   "EXTRA_CFLAGS",    ���o��ǰĿ��µ������ļ�(�������µ���Ŀ�)�O���~��ľ��g�x�, ���Բ��O��
   "CFLAGS_xxx.o",    ���o��ǰĿ��µ�xxx.c�O�����Լ��ľ��g�x�, ���Բ��O��

ע��: 
1. "subdir/"�е�б��"/"����ʡ��
2. 플�Makefile�е�CFLAGS�ھ��g����һ��.c�ļ��r����ʹ��
3. CFLAGS  EXTRA_CFLAGS  CFLAGS_xxx.o ���߽M��xxx.c�ľ��g�x�

����플�Ŀ䛵�Makefile��
   �����˶��xobj-y��ָ����Ŀ���Ҫ���M����ȥ���ļ�����Ŀ��⣬
   ��Ҫ�Ƕ��x�����ǰ�YCROSS_COMPILE,
   ���x���g����CFLAGS,
   ���x朽Ӆ���LDFLAGS,
   �@Щ���������ļ�����export�����ĸ�׃����

����플�Ŀ䛵�Makefile.build��
   �@�����}�s�Ĳ��֣����Ĺ��ܾ��ǰ�ĳ��Ŀ䛼�����������Ŀ��С���Ҫ���M����ȥ���ļ������g���������built-in.o
   Ԕ�����v��Ո��ҕ�l��

�ġ����Nʹ���@��Makefile��
1����플�Makefile, Makefile.build��������플�Ŀ�
   �ڸ�����Ŀ䛄���һ���հ׵�Makefile

2���_�����g��ЩԴ�ļ�
   �޸�플�Ŀ䛺͸�����Ŀ�Makefile��obj-y : 
    obj-y += xxx.o
	obj-y += yyy/
	�@��ʾҪ���g��ǰĿ��µ�xxx.c, Ҫ���g��ǰĿ��µ�yyy��Ŀ�	

3. �_�����g�x헡�朽��x�
   �޸�플�Ŀ�Makefile��CFLAGS���@�Ǿ��g����.c�ļ��r��Ҫ�õľ��g�x�;
   �޸�플�Ŀ�Makefile��LDFLAGS���@��朽�����đ��ó���r��朽��x�;
   
   �޸ĸ�����Ŀ��µ�Makefile��
   "EXTRA_CFLAGS",    ���o��ǰĿ��µ������ļ�(�������µ���Ŀ�)�O���~��ľ��g�x�, ���Բ��O��
   "CFLAGS_xxx.o",    ���o��ǰĿ��µ�xxx.c�O�����Լ��ľ��g�x�, ���Բ��O��
   
4. ʹ���Ă����g����
   �޸�플�Ŀ�Makefile��CROSS_COMPILE, �Á�ָ������朵�ǰ�Y(����arm-linux-)
   
5. �_�����ó�������֣�
   �޸�플�Ŀ�Makefile��TARGET, �@���Á�ָ�����g����ĳ��������

6. ����"make"���g������"make clean"�����������"make distclean"��ص����