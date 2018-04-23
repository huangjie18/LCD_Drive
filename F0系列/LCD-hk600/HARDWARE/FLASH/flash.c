/**
  ********************************  STM32F0xx  *********************************
  * @�ļ���     �� flash.c
  * @����       �� JieHuaHuang
  * @��汾     �� V1.5.0
  * @�ļ��汾   �� V1.0.0
  * @����       �� 2017��10��23
  * @ժҪ       �� ������ - flash��д
                   flash����EEPROM
  ******************************************************************************/
  
/* ������ͷ�ļ� --------------------------------------------------------------*/
#include "flash.h"

/* ���� ----------------------------------------------------------------------*/
volatile FLASH_Status  FLASHStatus = FLASH_COMPLETE;

/************************************************
�������� �� FLASH_PageWrite
��    �� �� дһҳFLASH
��    �� �� pBuffer ----- ���ݻ�����
            WriteAddr --- д��ַ
�� �� ֵ �� ��
��    �� �� huangjiehua
*************************************************/
void FLASH_PageWrite(uint16_t *pBuffer, uint32_t WriteAddr)
{
  uint16_t cnt_tmp;
  for(cnt_tmp=0; (cnt_tmp<FLASH_PAGE_LENGTH) && (FLASHStatus == FLASH_COMPLETE); cnt_tmp++)
  {
    FLASHStatus = FLASH_ProgramHalfWord(WriteAddr, *pBuffer);//һ��д��16λ���ݣ�2�ֽ�
    WriteAddr += 2;  //һ����ַ��һ���ֽ�����
    pBuffer++;
  }
}

/************************************************
�������� �� FLASH_WriteNWord
��    �� �� дFlash
��    �� �� pBuffer ----- ���ݻ�����
            WriteAddr --- д��ַ
            nWord ------- ����
�� �� ֵ �� ��
��    �� �� huangjiehua
*************************************************/
void FLASH_WriteNWord(uint16_t *pBuffer, uint32_t WriteAddr, uint16_t nWord)
{
  static uint16_t buf_tmp[FLASH_PAGE_LENGTH];
  uint32_t NbrOfPage = 0x00;                     //ҳ������д��

  uint32_t length_beyond_start;                  //��ʼҳ�����ĳ���(����)
  uint32_t length_remain_start;                  //��ʼҳʣ��ĳ���(����)

  uint32_t addr_first_page;                      //��һҳ(��ʼ)��ַ,�ڼ�ҳ��ʼ
  uint32_t addr_last_page;                       //���ҳ(��ʼ)��ַ
  uint16_t *pbuf_tmp;                            //bufָ��
  uint16_t cnt_length;                           //���� - ����
  uint16_t cnt_page;                             //���� - ҳ��
  uint32_t prog_addr_start;                      //��̵�ַ
  uint32_t length_beyond_last;                   //���ҳ�����ĳ���(����)
  uint8_t  flag_last_page_fill;                  //���һҳװ����־


  length_beyond_start = ((WriteAddr % FLASH_PAGE_SIZE) / FLASH_TYPE_LENGTH);//ҳƫ�Ƶ�ַ
  length_remain_start = FLASH_PAGE_LENGTH - length_beyond_start;  //ҳʣ���ַ
  addr_first_page     = WriteAddr - (WriteAddr % FLASH_PAGE_SIZE);//�õ�ҳ�Ŀ�ʼ��ַ�����ֵ�ַ����

  /* ����(д����)��ҳ�� */
  if(0 == (length_beyond_start + nWord)%FLASH_PAGE_LENGTH)//����պ�Ϊ<=512�ֽھͽ���
  {
    flag_last_page_fill = FLAG_OK;               //���һҳ�պ�
    NbrOfPage = (length_beyond_start + nWord) / FLASH_PAGE_LENGTH;//�õ�Ҫд��ҳ
  }
  else
  {
    flag_last_page_fill = FLAG_NOOK;             //��������ҳ
    NbrOfPage = (length_beyond_start + nWord) / FLASH_PAGE_LENGTH + 1;//�Ӷ�һҳ
  }

  /* ���� */
  FLASH_Unlock();

  /* �����־λ */
  FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_PGERR | FLASH_FLAG_WRPERR);

  /* ������һҳ */
  FLASH_ReadNWord(buf_tmp, addr_first_page, FLASH_PAGE_LENGTH); //ȡһҳ���ݳ�������ֹ��ʼ��ַ
                                                            //����ҳ��ʼ��ַ��������ҳʱ����֮ǰ������
  FLASHStatus = FLASH_ErasePage(addr_first_page); //����һҳ
  /* ֻ��1ҳ */
  if(1 == NbrOfPage)
  {
    pbuf_tmp = pBuffer;                          //���Ƶ�ַ(ָ��)
    for(cnt_length=length_beyond_start; cnt_length<(length_beyond_start + nWord); cnt_length++)
    {
      buf_tmp[cnt_length] = *pbuf_tmp;
      pbuf_tmp++;
    }//��Ҫд�����ݴ��buf_tmp
    FLASH_PageWrite(buf_tmp, addr_first_page);
  }
  /* ����1ҳ */
  else
  {
    /* ��һҳ */
    pbuf_tmp = pBuffer;
    for(cnt_length=length_beyond_start; cnt_length<FLASH_PAGE_LENGTH; cnt_length++)
    {
      buf_tmp[cnt_length] = *pbuf_tmp;
      pbuf_tmp++;
    }
    FLASH_PageWrite(buf_tmp, addr_first_page);

    /* ���һҳ�պ�װ�������ö�ȡ���һҳ���� */
    if(FLAG_OK == flag_last_page_fill)
    {
      for(cnt_page=1; (cnt_page<NbrOfPage)  && (FLASHStatus == FLASH_COMPLETE); cnt_page++)
      {                                          //�����̵�ַΪ�ֽڵ�ַ(��FLASH_PAGE_SIZE)
        prog_addr_start = addr_first_page + cnt_page*FLASH_PAGE_SIZE;
        FLASHStatus = FLASH_ErasePage(prog_addr_start);
                                                 //(cnt_page - 1):Ϊ��һҳ��ַ
        FLASH_PageWrite((pBuffer + length_remain_start + (cnt_page - 1)*FLASH_PAGE_LENGTH), prog_addr_start);
      }
    }
    else
    {
      /* �м�ҳ */
      for(cnt_page=1; (cnt_page<(NbrOfPage - 1))  && (FLASHStatus == FLASH_COMPLETE); cnt_page++)
      {                                          //�����̵�ַΪ�ֽڵ�ַ(��FLASH_PAGE_SIZE)
        prog_addr_start = addr_first_page + cnt_page*FLASH_PAGE_SIZE;
        FLASHStatus = FLASH_ErasePage(prog_addr_start);
                                                 //(cnt_page - 1):Ϊ��һҳ��ַ
        FLASH_PageWrite((pBuffer + length_remain_start + (cnt_page - 1)*FLASH_PAGE_LENGTH), prog_addr_start);
      }

      /* ���һҳ */
      addr_last_page = addr_first_page + (NbrOfPage - 1)*FLASH_PAGE_SIZE;

      FLASH_ReadNWord(buf_tmp, addr_last_page, FLASH_PAGE_LENGTH);
      FLASHStatus = FLASH_ErasePage(addr_last_page);
                                                 //NbrOfPage - 2: ��ҳ + ���һҳ ����ҳ(-2)
      pbuf_tmp = pBuffer + length_remain_start + (NbrOfPage - 2)*(FLASH_PAGE_SIZE/2);
      length_beyond_last   = (nWord - length_remain_start) % FLASH_PAGE_LENGTH;
      for(cnt_length=0; cnt_length<length_beyond_last; cnt_length++)
      {
        buf_tmp[cnt_length] = *pbuf_tmp;
        pbuf_tmp++;
      }
      FLASH_PageWrite(buf_tmp, addr_last_page);
    }
  }
}

/************************************************
�������� �� FLASH_ReadNWord
��    �� �� ��N��
��    �� �� pBuffer ----- ���ݻ�����
            ReadAddr ---- ����ַ
            nWord ------- ����
�� �� ֵ �� ��
��    �� �� huangjiehua
*************************************************/
void FLASH_ReadNWord(uint16_t* pBuffer, uint32_t ReadAddr, uint16_t nWord)
{
  while(nWord--)
  {
    *pBuffer = (*(__IO uint16_t*)ReadAddr); //��ȡ���ݱ����pBuffer��
    ReadAddr += 2;
    pBuffer++;
  }
}
