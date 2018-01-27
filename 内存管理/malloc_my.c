#define MEM1_BLOCK_SIZE 32   //定义一个内存块的32字节大小
#define MEM1_MAX_SIZE   100*1024  //最大偏移内存字节大小
#define MEM1_ALLOC_TABLE_SIZE   (MEM1_MAX_SIZE/MEM1_BLOCK_SIZE)  //可分为多少个内存管理

__align(32) u8 mem1base[MEM1_MAX_SIZE];   //在SRAM中定义一个数组，在此内存里实现malloc

u16 mem1mapbase[MEM1_ALLOC_TABLE_SIZE];   //内存管理表

u8 is_init_memory_ready = 0; //初始化标志符
/*
 * 1.首先要先对定义的数组初始化，也就是对该数组里的值都初始为0
 */
/**
 * [mymemset description]
 * @param s     [内存管理表数组指针]
 * @param c     [要初始化为0]
 * @param count [有多少个对应的数组内存块]
 */
void mymemset(void *s, u8 c, u32 count)
{
	u8 *xs = s;  //强制转换成u8指针，但地址不会变，只是对该指针加减的时候地址移动的距离变成u8
	while (count--)*xs++ = c;
}
/**
 * [my_mem_init 初始化各种数据]
 */
void my_mem_init(void)
{
	//对内存管理表初始化
	mymemset(mem1mapbase, 0, MEM1_ALLOC_TABLE_SIZE * 2); //因为指针变为u8了，所以要乘以2
	//对内存池初始化
	mymemset(mem1base, 0, MEM1_MAX_SIZE);
	//初始化标志位
	is_init_memory_ready = 1;
}
/**
 * [my_mem_malloc 内存申请]
 * @param size [申请的字节大小]
 */
u32 my_mem_malloc(u32 size)
{
	u32 nmemb;  //所需内存块
	signed long offset = 0; //因为整个内存块很大，所以用signed long类型
	u32 cmemb = 0;
	//如果未初始化
	if (is_init_memory_ready == 0)
	{
		my_mem_init(); //初始化
	}

	//如果申请的内存大小为0
	if (size == 0)
	{
		return 0xffffffff; //不需要分配
	}

	//得到需要多少个连续内存块
	nmemb = size / MEM1_BLOCK_SIZE;
	if (size % MEM1_BLOCK_SIZE) //如果有余数，则内存块需要加1
	{
		nmemb++;
	}
	//根据内存管理表搜索未使用的内存块,从后面开始检索
	for (offset = MEM1_ALLOC_TABLE_SIZE - 1; offset >= 0; offset--)
	{
		//找到未使用的内存块
		if (mem1mapbase[offset] == 0)
		{
			cmemb++; //要连续内存
		}
		else
		{
			cmemb = 0; //如果不连续就清零
		}
		//找到连续的空内存块等于所需内存块
		//提取该内存的地址和在内存管理表填入所申请的内存块数量
		if (cmemb == nmemb)
		{
			for (i = 0; i < nmemb; i++)
			{
				mem1mapbase[offset + i] = nmemb; //在内存管理表填入所申请的内存块数量
			}
			return (offset * MEM1_BLOCK_SIZE); //返回偏移地址
		}
	}
	return 0xffffffff;  //未找到符合分配条件的内存块
}
/**
 * [mymalloc description]
 * @param  size [内存大小]
 * @return      [内存指针]
 */
void *mymalloc(u32 size)
{
	u32 offset;
	offset = my_mem_malloc(size);
	if (offset == 0xffffffff)
	{
		return NULL;  //空指针
	}
	else
	{
		return (void *)((u32)mem1base + offset);
		//return (void *)(mem1base+offset);
	}
}
/**
 * [my_mem_free description]
 * @param  offset [内存偏移地址]
 * @return        [是否释放成功]
 */
char my_mem_free(u32 offset)
{
	int i;
	int index; //偏移所在号码
	int nmemb; //所占内存块数量
	//如果未初始化
	if (is_init_memory_ready == 0)
	{
		my_mem_init(); //初始化
		return -1;
	}
	//偏移在内存池内
	if (offset < MEM1_MAX_SIZE)
	{
		index = offset / MEM1_BLOCK_SIZE; //得到偏移所在内存块号码
		nmemb = mem1mapbase[index];    //内存块数量
		for (i = 0; i < nmemb; i++)
		{
			mem1mapbase[index + i] = 0;
		}
		return 1;
	}
	else
	{
		return 2;
	}
}
/**
 * [myfree description]
 * @param ptr [释放内存的指针]
 */
void myfree(void *ptr)
{
	u32 offset;
	if (ptr == NULL)
	{
		return;
	}
	offset = (32)ptr - (u32)mem1base; //得到偏移地址
	my_mem_free(offset);
}