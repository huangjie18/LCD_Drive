#include "DISPLAY_TFT.h"
#include "lcd.h"
#include "lcdfont.h"

u16 BACK_COLOR = GREEN; 
u16 POINT_COLOR = BLUE;   //����ɫ������ɫ

u16 colortbl[100];

u8 gundong[]=
{
0x02,0x08,0x22,0x3C,0x23,0xC8,0x22,0x08,0x22,0x28,0x22,0x1D,0x02,0x02,0x08,0x0C,
0x08,0x70,0xFF,0x80,0x08,0x02,0x08,0x01,0x08,0x02,0x0F,0xFC,0x00,0x00,0x00,0x00,/*"��",84*/
0x00,0x82,0x20,0x9C,0x21,0x00,0x21,0x00,0x22,0x3C,0x24,0x02,0x2A,0x02,0xF1,0x42,
0x28,0x32,0x24,0x02,0x22,0x02,0x21,0x0E,0x21,0x20,0x20,0x90,0x00,0x8C,0x00,0x00,/*"̬",86*/
0x20,0x00,0x22,0x10,0x21,0x90,0x28,0x1E,0x26,0x20,0xF0,0xC0,0x20,0x00,0x27,0xFC,
0x24,0x02,0xF4,0x02,0x24,0x42,0x24,0x22,0x27,0xC2,0x20,0x02,0x20,0x1E,0x00,0x00,/*"��",88*/
0x00,0x00,0x7F,0xFF,0x40,0x02,0x48,0x82,0x4A,0x82,0x4A,0x82,0x4A,0x82,0x7F,0xFE,
0x4A,0x82,0x4A,0x92,0x4A,0x8A,0x48,0xF2,0x40,0x02,0x7F,0xFF,0x00,0x00,0x00,0x00,/*"Χ",90*/
0x00,0x01,0x00,0x06,0x7F,0xF8,0x40,0x02,0x41,0x02,0x41,0x02,0x41,0x02,0x41,0x02,
0x5F,0xFE,0x41,0x02,0x41,0x02,0x41,0x22,0x41,0x1A,0x41,0x02,0x40,0x02,0x00,0x00,/*"ѹ",92*/
0x04,0x44,0x1C,0xE4,0xE7,0x48,0x0C,0x48,0x00,0x80,0x31,0x00,0x23,0xFF,0x2C,0x00,
0x24,0x00,0xA4,0xFF,0x65,0x92,0x26,0x92,0x24,0x92,0x24,0xFF,0x34,0x00,0x00,0x00,/*"��",94*/
};
/////////////////////////////////////////////////////////////////////////
//��ֲ�Ļ�ֻ��Ŀ���������LCDд���ݺ���,���㺯��ʹ�ÿ��ٻ���
/////////////////////////////////////////////////////////////////////////

void WriteDAT_16(u16 data)
{
	LCD_WR_para(data>>8);
	LCD_WR_para(data&0xff);
}
//��������
//x1,y1:�������
//x2,y2:�յ�����  
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 

	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//������� 
	{  
		LCD_DrawPoint(uRow,uCol);//���� 
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

//����
//POINT_COLOR:�˵����ɫ
void LCD_DrawPoint(u16 x,u16 y)
{
	LCD_qu(x,y,x,y);//���ù��λ�� 
	WriteDAT_16(POINT_COLOR); 	    
} 
//���ٻ���
void LCD_Fast_DrawPoint(u16 x,u16 y,u16 color)
{
	LCD_qu(x,y,x,y);//���ù��λ�� 
	WriteDAT_16(color); 	    
} 
//������
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}

//��ָ�����������ָ����ɫ
//�����С:
//  (xend-xsta)*(yend-ysta)
void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color)
{          
	u16 i,j; 
	LCD_qu(xsta,ysta,xend,yend);      //���ù��λ�� 
	for(i=ysta;i<=yend;i++)
	{													   	 	
		for(j=xsta;j<=xend;j++)WriteDAT_16(color);//���ù��λ�� 	    
	} 					  	    
}  

//��ָ��λ�û�һ��ָ����С��Բ
//(x,y):���ĵ�
//r    :�뾶
void Draw_Circle(u16 x0,u16 y0,u8 r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //�ж��¸���λ�õı�־
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
		//ʹ��Bresenham�㷨��Բ     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 
//		LCD_DrawPoint(x0+a,y0+b);
	}
} 
//��ˮƽ��
//x0,y0:����
//len:�߳���
//color:��ɫ
void gui_draw_hline(u16 x0,u16 y0,u16 len,u16 color)
{
	LCD_Fill(x0,y0,x0+len-1,y0,color);	
}
//��ʵ��Բ
//x0,y0:����
//r�뾶
//color:��ɫ
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

//����㺯��
//x0,y0:����
//color:��ɫ
//��(x0,y0)Ϊ����,��һ��9����Ĵ��
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
//��Բ�Ǿ���/���Բ�Ǿ���
//x,y,width,height:Բ�Ǿ��ε�λ�úͳߴ�
//r:Բ�ǵİ뾶.
//mode:0,�����ο�;1,������.
//downcolor:�ϰ벿����ɫ
//downcolor:�°벿����ɫ
void gui_draw_arcrectangle(u16 x,u16 y,u16 width,u16 height,u8 r,u8 mode,u16 downcolor)
{
	u16 btnxh=0;
	if(height%2)btnxh=height+1;//��ż������
	else btnxh=height;
	if(mode)//���
	{
 		gui_fill_rectangle(x+r,y,width-2*r,btnxh/2,downcolor);			//����
  		gui_fill_rectangle(x+r,y+btnxh/2,width-2*r,btnxh/2,downcolor);	//����
		gui_fill_rectangle(x,y+r,r,btnxh/2-r,downcolor);					//����
		gui_fill_rectangle(x,y+btnxh/2,r,btnxh/2-r,downcolor);			//����
		gui_fill_rectangle(x+width-r,y+r,r,btnxh/2-r,downcolor);			//����
		gui_fill_rectangle(x+width-r,y+btnxh/2,r,btnxh/2-r,downcolor);	//����
	}else
	{
		gui_draw_hline (x+r,y,width-2*r,downcolor);					//��		   
		gui_draw_hline (x+r,y+btnxh-1,width-2*r,downcolor);			//��		   
		gui_draw_vline (x,y+r,btnxh/2-r,downcolor);					//����		   
		gui_draw_vline (x,y+btnxh/2,btnxh/2-r,downcolor);			//����		   
		gui_draw_vline (x+width-1,y+r,btnxh/2-r,downcolor);			//����
		gui_draw_vline (x+width-1,y+btnxh/2,btnxh/2-r,downcolor);	//����				   
	}
	gui_draw_arc(x,y,x+r,y+r,x+r,y+r,r,downcolor,mode);//����	
	gui_draw_arc(x,y+btnxh-r,x+r,y+btnxh-1,x+r,y+btnxh-r-1,r,downcolor,mode);//����	
	gui_draw_arc(x+width-r,y,x+width,y+r,x+width-r-1,y+r,r,downcolor,mode);	 //����
	gui_draw_arc(x+width-r,y+btnxh-r,x+width,y+btnxh-1,x+width-r-1,y+btnxh-r-1,r,downcolor,mode);//����
}


//��ָ��λ�û�һ��ָ����С��Բ
//(rx,ry):Բ��
//(sx,sy),(ex,ey):�趨����ʾ��Χ
//r    :�뾶
//color:��ɫ
//mode :0,�����;1,���
void gui_draw_arc(u16 sx,u16 sy,u16 ex,u16 ey,u16 rx,u16 ry,u16 r,u16 color,u8 mode)
{
	int a,b,c;
	int di;	  
	a=0;b=r;	  
	di=3-(r<<1);	//�ж��¸���λ�õı�־
	while(a<=b)
	{
		if(mode)for(c=a;c<=b;c++)gui_draw_circle8(sx,sy,ex,ey,rx,ry,a,c,color);//��ʵ��Բ
 		else gui_draw_circle8(sx,sy,ex,ey,rx,ry,a,b,color);					   //������Բ
		a++;
		//ʹ��Bresenham�㷨��Բ     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 							  
	}
}
//����ֱ��
//x0,y0:����
//len:�߳���
//color:��ɫ
void gui_draw_vline(u16 x0,u16 y0,u16 len,u16 color)
{
	LCD_Fill(x0,y0,x0,y0+len-1,color);	
}

//������
//x0,y0:���ε����Ͻ�����
//width,height:���εĳߴ�
//color:��ɫ
void gui_fill_rectangle(u16 x0,u16 y0,u16 width,u16 height,u16 color)
{	  	
	
	if(width==0||height==0)return;//�Ƿ�.	 
	LCD_Fill(x0,y0,x0+width-1,y0+height-1,color);	   	   
}

//��8��(Bresenham�㷨)		  
//(sx,sy),(ex,ey):�趨����ʾ��Χ
//(rx,ry,a,b):����
//color:��ɫ
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

//�������ڻ���
//(sx,sy),(ex,ey):�趨����ʾ��Χ
//(x,y):������
//color:��ɫ
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

//��һ����ɫƽ�����ɵ�����һ����ɫ
//srgb,ergb:��ʼ��ɫ����ֹ��ɫ.
//cbuf:��ɫ������(��len)
//len:���ɼ���(�����������ɫֵ����)
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

//��һ��ƽ�����ɵĲ�ɫ����(����)
//x,y,width,height:���ε�����ߴ�
//srgb,ergb:��ʼ����ֹ����ɫ
void gui_draw_smooth_rectangle(u16 x,u16 y,u16 width,u16 height,u32 srgb,u32 ergb)
{
	u16 i,j;
//	gui_smooth_color(srgb,ergb,colortbl,height);//�����ɫ�飬��ע������ɫ�����й���
 	for(i=0;i<height;i++)
	{	 
		for(j=0;j<width;j++)
		{
			LCD_Fast_DrawPoint(x+j,y-i,colortbl[i]);//����
		}
	}

}


//��ʾ�ַ���
//x,y:�������
//width,height:�����С  
//size:�����С
//*p:�ַ�����ʼ��ַ		  
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,char *p)
{  	
	u8 x0=x;
	width+=x;
	height+=y;
    while((*p<='~')&&(*p>=' '))//�ж��ǲ��ǷǷ��ַ�!
    {       
        if(x>=width){x=x0;y+=size;}
        if(y>=height)break;//�˳�
        LCD_ShowChar(x,y,*p,size,1);
		if(size==18) //����
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

//��ָ��λ����ʾһ���ַ�
//x,y:��ʼ����
//num:Ҫ��ʾ���ַ�:" "--->"~"
//size:�����С 12/16/24
//mode:���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode)
{  	
	
    u8 temp,t1,t;
	u16 y0=y;
	u8 csize;
	if(size==18)  //����
	{
		csize = 16; 
	}
	else
	{
		csize=(size/8+((size%8)?1:0))*(size/2);		//�õ�����һ���ַ���Ӧ������ռ���ֽ���
	}		
 	num=num-' ';//�õ�ƫ�ƺ��ֵ��ASCII�ֿ��Ǵӿո�ʼȡģ������-' '���Ƕ�Ӧ�ַ����ֿ⣩
	for(t=0;t<csize;t++)
	{   

		if(size==12)temp=asc2_1206[num][t]; 	 	//����1206����
		else if(size==16)temp=asc2_1608[num][t];	//����1608����
//		else if(size==18)temp=asc2_1608_chu[num][t]; //����1608������
//		else if(size==24)temp=asc2_2412[num][t];	//����2412����
		else return;								//û�е��ֿ�
		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)LCD_Fast_DrawPoint(x,y,POINT_COLOR);
			else if(mode==0)LCD_Fast_DrawPoint(x,y,BACK_COLOR);
			temp<<=1;
			y++;
			if(y>=160)return;		//��������
			if(size==18)
			{
				if((y-y0)==16)
				{
					y=y0;   //��Ϊ˳���������£������ң�һ���������һ��
					x++;
					if(x>=128)return;	//��������
					break;
				}
			}
			else
			{
				if((y-y0)==size)
				{
					y=y0;   //��Ϊ˳���������£������ң�һ���������һ��
					x++;
					if(x>=128)return;	//��������
					break;
				}
			}
		}  	 
	}  	    	   	 	  
}   


//
//���ý���ɫ��������
//��x,y�ĵط������߶�height,���weight������
void Colorful_Music_DisplayA(u16 x, u16 y, u16 height, u16 weight)
{
		u8 i;
		u16 color;
		for(i=0; i<height; i++)//����ɫ
	  {
				if(i<47) color = 0xFA08+32*i;
				else if((i>=47)&&(i<70)) color =0xFFE8-2048*(i-47);
				else if((i>=70)&&(i<93)) color=0x47E8+(i-70);
				else if((i>=93)&&(i<140)) color= 0x47FF-(i-93)*32;
				else if((i>=140)&&(i<160)) color= 0x421F+(i-140)*2048;
				Fill_Fast_Rec(x+160-i, y, 1, weight, color);
		}
//		Fill_Fast_Rec(x, y, 161-height, weight, GRAY1);  //161-height������ʾGRAY1ɫ
}

//���趨����ɫ���ĳ������
void Fill_Fast_Rec(uint16_t X_Start , uint16_t Y_Start, uint16_t x_width, uint16_t y_hight,uint16_t color)
{
    uint16_t h,v;
    LCD_qu(X_Start,Y_Start,x_width,y_hight);
    for(h=0;h<y_hight;h++)
       for(v=0;v<x_width;v++)
						WriteDAT_16(color);//д��ɫ
//		 TFT_DrawPoint(X_Start+v,Y_Start+h,color);
//           Write_Two_Byte_Data(color);//д����ɫ
     LCD_qu(0,0,127,159);//���¿�������ȫ����ʾ      
}

//��ָ��λ����ʾһ������
//x,y:��ʼ����
//num:Ҫ��ʾ�ĺ���:
//size:�����С 12/16/24
//mode:���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)
void LCD_ShowChar_CN(u16 x,u16 y,u8 num,u8 size,u8 mode)
{
	u8 temp=0;
	u8 t_cn=0; 
	u8 t1_cn=0;
	u8 num_b;
	u16 y0=y;
	u8 csize_cn=32; //32�ֽ�
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
			if(y>127) //��y������
			{
				return;
			}
			if((y-y0)==size) //y����д��size�Σ�����ȡģ˳��Ӧת����һ��,
			{
				y = y0;
				x++;
				if(x>63)
					return; //��x������
				break;
			}
		}
	}
	   	   	 	
}


//������ʾ��̬��Χѹ��
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
//				if(y>127) //��y������
//				{
//					return;
//				}
				if((y-y0)==size) //y����д��size�Σ�����ȡģ˳��Ӧת����һ��,
				{
					y = y0;
					x++;
					if(x>63)
						x=0; //��x������
					break;
				}
			}
		}
		delay_ms(150);
		start = start + 2;
	}
}