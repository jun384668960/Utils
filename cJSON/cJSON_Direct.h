#ifndef _CJSON_DIRECT_H_
#define _CJSON_DIRECT_H_


typedef enum {
	KEY_TYPE_NULL,
	KEY_TYPE_U8,
	KEY_TYPE_U16,
	KEY_TYPE_U32,
	KEY_TYPE_FLOAT,
	KEY_TYPE_DOUBLE,
	KEY_TYPE_STRING,
	KEY_TYPE_OBJECT,
	KEY_TYPE_ARRAY,///< ע�⣬���ڻ������飬ֻ֧��32λ
	KEY_TYPE_MAX
}key_type_e;


typedef struct key_info_s{
	int csize;					///< ���ṹ���С
	key_type_e type;				///< ��Ա����
	char *key;					///< ��Ա����
	int offset;					///< ��Աƫ�Ƶ�ַ
	int ksize;						///< ��Ա��С
	struct key_info_s *sub_key;	///< ����#KEY_TYPE_OBJECT���ͣ���������Ͷ���
	int arraycnt;					///< ����#KEY_TYPE_ARRAY���ͣ������
	key_type_e arraytype;		///< ����#KEY_TYPE_ARRAY���ͣ����Ա������
}key_info_t;


/*��Ա�ڽṹ���е�ƫ�Ƶ�ַ*/
#define NAME_OFFSET(type,name) ((int)(&(((type *)0)->name)))
#define NAME_SIZE(type,name) (sizeof((((type *)0)->name)))


/**
 *@brief �γɽṹ��
 *@param ctype �ṹ������
 *@param ktype ��Ա����
 *@param kname ��Ա��
 *@param subkey ���keytypeΪ#KEY_TYPE_OBJECT����Ϊ���Ӧ�ṹ���#key_info_t ָ��
 *@param arraycnt ����#KEY_TYPE_ARRAY���ͣ������
 *@param arraytype ����#KEY_TYPE_ARRAY���ͣ����Ա������
 *
 */
#define MAKE_ARRAY_INFO(ctype, ktype, kname, subkey, arraycnt, arraytype) {sizeof(ctype), ktype, #kname, NAME_OFFSET(ctype,kname), NAME_SIZE(ctype,kname), subkey, arraycnt, arraytype}

#define MAKE_KEY_INFO(ctype, ktype, kname, subkey) MAKE_ARRAY_INFO(ctype, ktype, kname, subkey, 0, KEY_TYPE_NULL)
#define MAKE_END_INFO()	{0, KEY_TYPE_NULL, NULL, 0, 0, NULL}


/**
 *@brief 
 *@param kinfo ���� �ṹ����Ϣ������ʶ��ṹ�����Ա
 *@param string ���� Ҫת�����ַ���
 *@param obj ��� �ṹ��ָ�롣���ΪNULL�����Զ������ڴ棬��Ҫ�ͷ�
 *
 *@return obj��ʧ��ʱ����NULL
 *
 */
void *cjson_string2object(key_info_t *kinfo, char *string, void *obj);

/**
 *@brief 
 *@param kinfo ���� �ṹ����Ϣ������ʶ��ṹ�����Ա
 *@param obj ���� Ҫת���Ľṹ���ַ
 *
 *@return json��ʽ���ַ�����NULL if failed
 *
 *@note �䷵�ص��ַ�������Ҫ��free�ͷ�
 *
 */
char *cjson_object2string(key_info_t *kinfo, void *obj);

#endif

