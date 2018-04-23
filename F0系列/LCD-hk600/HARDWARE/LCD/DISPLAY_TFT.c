#include "DISPLAY_TFT.h"
#include "lcd.h"
#include "lcdfont.h"

u16 BACK_COLOR = GREEN; 
u16 POINT_COLOR = BLUE;   //背景色，画笔色

u16 colortbl[100];

u8 gundong[]=
{
0x02,0x08,0x22,0x3C,0x23,0xC8,0x22,0x08,0x22,0x28,0x22,0x1D,0x02,0x02,0x08,0x0C,
0x08,0x70,0xFF,0x80,0x08,0x02,0x08,0x01,0x08,0x02,0x0F,0xFC,0x00,0x00,0x00,0x00,/*"动",84*/
0x00,0x82,0x20,0x9C,0x21,0x00,0x21,0x00,0x22,0x3C,0x24,0x02,0x2A,0x02,0xF1,0x42,
0x28,0x32,0x24,0x02,0x22,0x02,0x21,0x0E,0x21,0x20,0x20,0x90,0x00,0x8C,0x00,0x00,/*"态",86*/
0x20,0x00,0x22,0x10,0x21,0x90,0x28,0x1E,0x26,0x20,0xF0,0xC0,0x20,0x00,0x27,0xFC,
0x24,0x02,0xF4,0x02,0x24,0x42,0x24,0x22,0x27,0xC2,0x20,0x02,0x20,0x1E,0x00,0x00,/*"范",88*/
0x00,0x00,0x7F,0xFF,0x40,0x02,0x48,0x82,0x4A,0x82,0x4A,0x82,0x4A,0x82,0x7F,0xFE,
0x4A,0x82,0x4A,0x92,0x4A,0x8A,0x48,0xF2,0x40,0x02,0x7F,0xFF,0x00,0x00,0x00,0x00,/*"围",90*/
0x00,0x01,0x00,0x06,0x7F,0xF8,0x40,0x02,0x41,0x02,0x41,0x02,0x41,0x02,0x41,0x02,
0x5F,0xFE,0x41,0x02,0x41,0x02,0x41,0x22,0x41,0x1A,0x41,0x02,0x40,0x02,0x00,0x00,/*"压",92*/
0x04,0x44,0x1C,0xE4,0xE7,0x48,0x0C,0x48,0x00,0x80,0x31,0x00,0x23,0xFF,0x2C,0x00,
0x24,0x00,0xA4,0xFF,0x65,0x92,0x26,0x92,0x24,0x92,0x24,0xFF,0x34,0x00,0x00,0x00,/*"缩",94*/
};
/////////////////////////////////////////////////////////////////////////
//移植的话只需改开区函数和LCD写数据函数,画点函数使用快速画点
/////////////////////////////////////////////////////////////////////////

void WriteDAT_16(u16 data)
{
	LCD_WR_para(data>>8);
	LCD_WR_para(data&0xff);
}
//画任意线
//x1,y1:起点坐标
//x2,y2:终点坐标  
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 

	delta_x=x2-x1; //计算坐标增量 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //设置单步方向 
	else if(delta_x==0)incx=0;//垂直线 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//水平线 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //选取基本增量坐标轴 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//画线输出 
	{  
		LCD_DrawPoint(uRow,uCol);//画点 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}  

//画点
//POINT_COLOR:此点的颜色
void LCD_DrawPoint(u16 x,u16 y)
{
	LCD_qu(x,y,x,y);//设置光标位置 
	WriteDAT_16(POINT_COLOR); 	    
} 
//快速画点
void LCD_Fast_DrawPoint(u16 x,u16 y,u16 color)
{
	LCD_qu(x,y,x,y);//设置光标位置 
	WriteDAT_16(color); 	    
} 
//画矩形
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}

//在指定区域内填充指定颜色
//区域大小:
//  (xend-xsta)*(yend-ysta)
void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color)
{          
	u16 i,j; 
	LCD_qu(xsta,ysta,xend,yend);      //设置光标位置 
	for(i=ysta;i<=yend;i++)
	{													   	 	
		for(j=xsta;j<=xend;j++)WriteDAT_16(color);//设置光标位置 	    
	} 					  	    
}  

//在指定位置画一个指定大小的圆
//(x,y):中心点
//r    :半径
void Draw_Circle(u16 x0,u16 y0,u8 r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //判断下个点位置的标志
	while(a<=b)
	{
		LCD_DrawPoint(x0-b,y0-a);             //3           
		LCD_DrawPoint(x0+b,y0-a);             //0           
		LCD_DrawPoint(x0-a,y0+b);             //1       
		LCD_DrawPoint(x0-b,y0-a);             //7           
		LCD_DrawPoint(x0-a,y0-b);             //2             
		LCD_DrawPoint(x0+b,y0+a);             //4               
		LCD_DrawPoint(x0+a,y0-b);             //5
		LCD_DrawPoint(x0+a,y0+b);             //6 
		LCD_DrawPoint(x0-b,y0+a);             
		a++;
		//使用Bresenham算法画圆     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 
//		LCD_DrawPoint(x0+a,y0+b);
	}
} 
//画水平线
//x0,y0:坐标
//len:线长度
//color:颜色
void gui_draw_hline(u16 x0,u16 y0,u16 len,u16 color)
{
	LCD_Fill(x0,y0,x0+len-1,y0,color);	
}
//画实心圆
//x0,y0:坐标
//r半径
//color:颜色
void gui_fill_circle(u16 x0,u16 y0,u16 r,u16 color)
{											  
	u32 i;
	u32 imax = ((u32)r*707)/1000+1;
	u32 sqmax = (u32)r*(u32)r+(u32)r/2;
	u32 x=r;
	gui_draw_hline(x0-r,y0,2*r,color);
	for (i=1;i<=imax;i++) 
	{
		if ((i*i+x*x)>sqmax) 
		{
			// draw lines from outside  
			if (x>imax) 
			{
				gui_draw_hline (x0-i+1,y0+x,2*(i-1),color);
				gui_draw_hline (x0-i+1,y0-x,2*(i-1),color);
			}
			x--;
		}
		// draw lines from inside (center)  
		gui_draw_hline(x0-x,y0+i,2*x,color);
		gui_draw_hline(x0-x,y0-i,2*x,color);
	}
}

//画大点函数
//x0,y0:坐标
//color:颜色
//以(x0,y0)为中心,画一个9个点的大点
void gui_draw_bigpoint(u16 x0,u16 y0,u16 color)
{
	u16 i,j;
	u16 x,y;				    
	if(x0>=1)x=x0-1;
	else x=x0;
	if(y0>=1)y=y0-1;
	else y=y0;
	for(i=y;i<y0+2;i++)
	{
		for(j=x;j<x0+2;j++)LCD_Fast_DrawPoint(j,i,color);
	}  						   
}

/////////////////////////////////////////////////
//画圆角矩形/填充圆角矩形
//x,y,width,height:圆角矩形的位置和尺寸
//r:圆角的半径.
//mode:0,画矩形框;1,填充矩形.
//downcolor:上半部分颜色
//downcolor:下半部分颜色
void gui_draw_arcrectangle(u16 x,u16 y,u16 width,u16 height,u8 r,u8 mode,u16 downcolor)
{
	u16 btnxh=0;
	if(height%2)btnxh=height+1;//基偶数处理
	else btnxh=height;
	if(mode)//填充
	{
 		gui_fill_rectangle(x+r,y,width-2*r,btnxh/2,downcolor);			//中上
  		gui_fill_rectangle(x+r,y+btnxh/2,width-2*r,btnxh/2,downcolor);	//中下
		gui_fill_rectangle(x,y+r,r,btnxh/2-r,downcolor);					//左上
		gui_fill_rectangle(x,y+btnxh/2,r,btnxh/2-r,downcolor);			//左下
		gui_fill_rectangle(x+width-r,y+r,r,btnxh/2-r,downcolor);			//右上
		gui_fill_rectangle(x+width-r,y+btnxh/2,r,btnxh/2-r,downcolor);	//右下
	}else
	{
		gui_draw_hline (x+r,y,width-2*r,downcolor);					//上		   
		gui_draw_hline (x+r,y+btnxh-1,width-2*r,downcolor);			//下		   
		gui_draw_vline (x,y+r,btnxh/2-r,downcolor);					//左上		   
		gui_draw_vline (x,y+btnxh/2,btnxh/2-r,downcolor);			//左下		   
		gui_draw_vline (x+width-1,y+r,btnxh/2-r,downcolor);			//右上
		gui_draw_vline (x+width-1,y+btnxh/2,btnxh/2-r,downcolor);	//右下				   
	}
	gui_draw_arc(x,y,x+r,y+r,x+r,y+r,r,downcolor,mode);//左上	
	gui_draw_arc(x,y+btnxh-r,x+r,y+btnxh-1,x+r,y+btnxh-r-1,r,downcolor,mode);//左下	
	gui_draw_arc(x+width-r,y,x+width,y+r,x+width-r-1,y+r,r,downcolor,mode);	 //右上
	gui_draw_arc(x+width-r,y+btnxh-r,x+width,y+btnxh-1,x+width-r-1,y+btnxh-r-1,r,downcolor,mode);//右下
}


//在指定位置画一个指定大小的圆
//(rx,ry):圆心
//(sx,sy),(ex,ey):设定的显示范围
//r    :半径
//color:颜色
//mode :0,不填充;1,填充
void gui_draw_arc(u16 sx,u16 sy,u16 ex,u16 ey,u16 rx,u16 ry,u16 r,u16 color,u8 mode)
{
	int a,b,c;
	int di;	  
	a=0;b=r;	  
	di=3-(r<<1);	//判断下个点位置的标志
	while(a<=b)
	{
		if(mode)for(c=a;c<=b;c++)gui_draw_circle8(sx,sy,ex,ey,rx,ry,a,c,color);//画实心圆
 		else gui_draw_circle8(sx,sy,ex,ey,rx,ry,a,b,color);					   //画空心圆
		a++;
		//使用Bresenham算法画圆     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 							  
	}
}
//画垂直线
//x0,y0:坐标
//len:线长度
//color:颜色
void gui_draw_vline(u16 x0,u16 y0,u16 len,u16 color)
{
	LCD_Fill(x0,y0,x0,y0+len-1,color);	
}

//填充矩形
//x0,y0:矩形的左上角坐标
//width,height:矩形的尺寸
//color:颜色
void gui_fill_rectangle(u16 x0,u16 y0,u16 width,u16 height,u16 color)
{	  	
	
	if(width==0||height==0)return;//非法.	 
	LCD_Fill(x0,y0,x0+width-1,y0+height-1,color);	   	   
}

//画8点(Bresenham算法)		  
//(sx,sy),(ex,ey):设定的显示范围
//(rx,ry,a,b):参数
//color:颜色
void gui_draw_circle8(u16 sx,u16 sy,u16 ex,u16 ey,u16 rx,u16 ry,int a,int b,u16 color)
{
	gui_draw_expoint(sx,sy,ex,ey,rx+a,ry-b,color);              
	gui_draw_expoint(sx,sy,ex,ey,rx+b,ry-a,color);                       
	gui_draw_expoint(sx,sy,ex,ey,rx+b,ry+a,color);                           
	gui_draw_expoint(sx,sy,ex,ey,rx+a,ry+b,color);             
	gui_draw_expoint(sx,sy,ex,ey,rx-a,ry+b,color);                  
	gui_draw_expoint(sx,sy,ex,ey,rx-b,ry+a,color);               
	gui_draw_expoint(sx,sy,ex,ey,rx-b,ry-a,color);                      
	gui_draw_expoint(sx,sy,ex,ey,rx-a,ry-b,color);                  
}	

//在区域内画点
//(sx,sy),(ex,ey):设定的显示范围
//(x,y):点坐标
//color:颜色
void gui_draw_expoint(u16 sx,u16 sy,u16 ex,u16 ey,u16 x,u16 y,u16 color)	    
{
	u16 tempcolor;
	if(x<=ex&&x>=sx&&y<=ey&&y>=sy)
	{
		tempcolor=POINT_COLOR;
		POINT_COLOR=color;
		LCD_DrawPoint(x,y);	    
		POINT_COLOR=tempcolor;
	}
}

//将一种颜色平滑过渡到另外一种颜色
//srgb,ergb:起始颜色和终止颜色.
//cbuf:颜色缓存区(≥len)
//len:过渡级数(就是输出的颜色值总数)
void gui_smooth_color(u32 srgb,u32 ergb,u16*cbuf,u16 len)
{
	u8 sr,sg,sb;
	short dr,dg,db;
	u16 r,g,b;	  
	u16 i=0;
	///////////////
// 	sr=srgb>>16;
//	sg=(srgb>>8)&0XFF;
//	sb=srgb&0XFF;
//	dr=(ergb>>16)-sr;
//	dg=((ergb>>8)&0XFF)-sg;
//	db=(ergb&0XFF)-sb;
	/////////////////
	sb=srgb>>16;
	sg=(srgb>>8)&0XFF;
	sr=srgb&0XFF;
	db=(ergb>>16)-sr;
	dg=((ergb>>8)&0XFF)-sg;
	dr=(ergb&0XFF)-sb;
 	for(i=0;i<len;i++)
	{
	 	r=sr+(dr*i)/len;
 	 	g=sg+(dg*i)/len;
	 	b=sb+(db*i)/len;
		r>>=3;
		g>>=2;
		b>>=3;
	    cbuf[i]=((r<<11)|(g<<5)|b);		   
	}
}

//画一条平滑过渡的彩色矩形(或线)
//x,y,width,height:矩形的坐标尺寸
//srgb,ergb:起始和终止的颜色
void gui_draw_smooth_rectangle(u16 x,u16 y,u16 width,u16 height,u32 srgb,u32 ergb)
{
	u16 i,j;
//	gui_smooth_color(srgb,ergb,colortbl,height);//获得颜色组，不注释则颜色柱都有过渡
 	for(i=0;i<height;i++)
	{	 
		for(j=0;j<width;j++)
		{
			LCD_Fast_DrawPoint(x+j,y-i,colortbl[i]);//画点
		}
	}

}


//显示字符串
//x,y:起点坐标
//width,height:区域大小  
//size:字体大小
//*p:字符串起始地址		  
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,char *p)
{  	
	u8 x0=x;
	width+=x;
	height+=y;
    while((*p<='~')&&(*p>=' '))//判断是不是非法字符!
    {       
        if(x>=width){x=x0;y+=size;}
        if(y>=height)break;//退出
        LCD_ShowChar(x,y,*p,size,1);
		if(size==18) //粗体
		{
			x+=16/2;
		}
		else
		{
			x+=size/2;
		}
        p++;
    }  
}

//在指定位置显示一个字符
//x,y:起始坐标
//num:要显示的字符:" "--->"~"
//size:字体大小 12/16/24
//mode:叠加方式(1)还是非叠加方式(0)
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode)
{  	
	
    u8 temp,t1,t;
	u16 y0=y;
	u8 csize;
	if(size==18)  //粗体
	{
		csize = 16; 
	}
	else
	{
		csize=(size/8+((size%8)?1:0))*(size/2);		//得到字体一个字符对应点阵集所占的字节数
	}		
 	num=num-' ';//得到偏移后的值（ASCII字库是从空格开始取模，所以-' '就是对应字符的字库）
	for(t=0;t<csize;t++)
	{   

		if(size==12)temp=asc2_1206[num][t]; 	 	//调用1206字体
		else if(size==16)temp=asc2_1608[num][t];	//调用1608字体
//		else if(size==18)temp=asc2_1608_chu[num][t]; //调用1608粗字体
//		else if(size==24)temp=asc2_2412[num][t];	//调用2412字体
		else return;								//没有的字库
		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)LCD_Fast_DrawPoint(x,y,POINT_COLOR);
			else if(mode==0)LCD_Fast_DrawPoint(x,y,BACK_COLOR);
			temp<<=1;
			y++;
			if(y>=160)return;		//超区域了
			if(size==18)
			{
				if((y-y0)==16)
				{
					y=y0;   //因为顺序是上往下，左往右，一列移完后下一列
					x++;
					if(x>=128)return;	//超区域了
					break;
				}
			}
			else
			{
				if((y-y0)==size)
				{
					y=y0;   //因为顺序是上往下，左往右，一列移完后下一列
					x++;
					if(x>=128)return;	//超区域了
					break;
				}
			}
		}  	 
	}  	    	   	 	  
}   


//
//利用渐变色产生音柱
//在x,y的地方产生高度height,宽度weight的音柱
void Colorful_Music_DisplayA(u16 x, u16 y, u16 height, u16 weight)
{
		u8 i;
		u16 color;
		for(i=0; i<height; i++)//填充彩色
	  {
				if(i<47) color = 0xFA08+32*i;
				else if((i>=47)&&(i<70)) color =0xFFE8-2048*(i-47);
				else if((i>=70)&&(i<93)) color=0x47E8+(i-70);
				else if((i>=93)&&(i<140)) color= 0x47FF-(i-93)*32;
				else if((i>=140)&&(i<160)) color= 0x421F+(i-140)*2048;
				Fill_Fast_Rec(x+160-i, y, 1, weight, color);
		}
//		Fill_Fast_Rec(x, y, 161-height, weight, GRAY1);  //161-height部分显示GRAY1色
}

//以设定的颜色填充某个区域
void Fill_Fast_Rec(uint16_t X_Start , uint16_t Y_Start, uint16_t x_width, uint16_t y_hight,uint16_t color)
{
    uint16_t h,v;
    LCD_qu(X_Start,Y_Start,x_width,y_hight);
    for(h=0;h<y_hight;h++)
       for(v=0;v<x_width;v++)
						WriteDAT_16(color);//写颜色
//		 TFT_DrawPoint(X_Start+v,Y_Start+h,color);
//           Write_Two_Byte_Data(color);//写入颜色
     LCD_qu(0,0,127,159);//重新开窗可以全副显示      
}

//在指定位置显示一个汉字
//x,y:起始坐标
//num:要显示的汉字:
//size:字体大小 12/16/24
//mode:叠加方式(1)还是非叠加方式(0)
void LCD_ShowChar_CN(u16 x,u16 y,u8 num,u8 size,u8 mode)
{
	u8 temp=0;
	u8 t_cn=0; 
	u8 t1_cn=0;
	u8 num_b;
	u16 y0=y;
	u8 csize_cn=32; //32字节
	for(t_cn=0;t_cn<csize_cn;t_cn++)
	{
		if(t_cn>15)
		{
			temp = asc2_1616_CN[num+1][t_cn-16];
		}
		else
		{
			temp = asc2_1616_CN[num][t_cn];
		}
		for(t1_cn=0;t1_cn<8;t1_cn++)
		{
			if(temp&0x80)
				LCD_Fast_DrawPoint(x,y,POINT_COLOR);
			else if(0 == mode)
				LCD_Fast_DrawPoint(x,y,BACK_COLOR);
			temp<<=1;
			y++;
			if(y>127) //超y区域了
			{
				return;
			}
			if((y-y0)==size) //y方向写了size次，符合取模顺序应转到下一列,
			{
				y = y0;
				x++;
				if(x>63)
					return; //超x区域了
				break;
			}
		}
	}
	   	   	 	
}


//滚动显示动态范围压缩
void gundong_1(u16 x,u16 y,u8 num,u8 size,u8 mode)
{
	u8 temp=0;
	u8 i;
	u8 b;
	u16 y0=y;
	u8 start=0;
	while(1)
	{
		if(start>63)
		{
			start = 0;
			delay_ms(500);
		}	
		for(b=0;b<128;b++)
		{
			temp = gundong[start+b];
			for(i=0;i<8;i++)
			{
				if(temp&0x80)
						LCD_Fast_DrawPoint(x,y,POINT_COLOR);
				else if(0 == mode)
						LCD_Fast_DrawPoint(x,y,BACK_COLOR);
				temp<<=1;
				y++;
//				if(y>127) //超y区域了
//				{
//					return;
//				}
				if((y-y0)==size) //y方向写了size次，符合取模顺序应转到下一列,
				{
					y = y0;
					x++;
					if(x>63)
						x=0; //超x区域了
					break;
				}
			}
		}
		delay_ms(150);
		start = start + 2;
	}
}