/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id ini.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-11-26 9:41:11
 * @uses ini file opration class
 */
#ifndef PAP_COMMON_BASE_INI_H_
#define PAP_COMMON_BASE_INI_H_

#include "common/file/config.h"

#define ERROR_DATA -99999999
#define INI_VALUE_MAX 1024

namespace pap_common_file {

class Ini {

 public: //base functions
   Ini();
   Ini(const char* file_name);
   virtual ~Ini();
   char* get_data();
   int32_t get_lines();
   bool open(const char* file_name);
   void close();
   bool save(char* file_name = NULL);
   const int32_t get_title_index(const char* title);
 
 public: //out useful functions
   int64_t read_int64(const char* section, const char* key);
   int64_t read_int64(const char* section, int32_t line);
   bool read_exist_int64(const char* section, const char* key, int64_t &result);
   float read_float(const char* section, const char* key);
   bool read_bool(const char* section, const char* key); //all large than 0 is true
   int32_t read_int32(const char* section, const char* key);
   uint32_t read_uint32(const char* section, const char* key);
   int16_t read_int16(const char* section, const char* key);
   uint16_t read_uint16(const char* section, const char* key);
   int8_t read_int8(const char* section, const char* key);
   uint8_t read_uint8(const char* section, const char* key);
   bool read_exist_int32(const char* section, const char* key, int32_t &result);
   bool read_exist_uint32(const char* section, const char* key, uint32_t &result);
   bool read_exist_int16(const char* section, const char* key, int16_t &result);
   bool read_exist_uint16(const char* section, const char* key, uint16_t &result);
   bool read_exist_int8(const char* section, const char* key, int8_t &result);
   bool read_exist_uint8(const char* section, const char* key, uint8_t &result);
   int32_t read_int32(const char* section, int32_t line);
   uint32_t read_uint32(const char* section, int32_t line);
   int16_t read_int16(const char* section, int32_t line);
   uint16_t read_uint16(const char* section, int32_t line);
   int8_t read_int8(const char* section, int32_t line);
   uint8_t read_uint8(const char* section, int32_t line);
   void read_text(const char* section, const char* key, char* str, int32_t length);
   bool read_exist_text(const char* section, const char* key, char* str, int32_t length);
   void read_text(const char* section, int32_t line, char* str, int32_t length);
   void read_key(const char* section, int32_t line, char* str, int32_t length); //在指定行读一字符名称
   bool write(const char* section, const char* key, int32_t value); //写一个32位整数
   bool write(const char* section, const char* key, const char* value); //写一个字符串
   int32_t get_continue_data_number(const char* section); //返回连续的行数（从section到第一个空行）
   char* read_one_line(int32_t line); //从指定行上读取数据
   int32_t find_one_line(int32_t line); //查找行，不存在则返回-1
   int32_t get_line_number(const char* str); //获取指定字符串所在的行数

 private:
   char* file_name_[FILENAME_MAX];
   int64_t data_length_;
   char* data_info_;
   int32_t section_number_; //索引的数量（[]的数目）
   int32_t* section_list_; //数据索列表
   int32_t point_; //当前指针
   int32_t line_, row_; //当前行列
   char value_[INI_VALUE_MAX];
   char ret_[INI_VALUE_MAX];

 private:
   void init_index();
   int32_t find_key_index(const char* key);
   int32_t find_data_index(int32_t postion, const char* data); //返回数据所在的索引
   int32_t goto_next_line(int32_t line); //提行
   char* find_key(int32_t &postion); //在指定位置读取键
   char* read_text(int32_t postion); //在指定位置读取字符串
   bool add_section(const char* section); //添加一个节点
   bool add_data(int32_t index, const char* key, const char* value); //在当前位置加入数据
   bool modify_data(int32_t index, const char* key, const char* value); //在当前位置修改数据
   int32_t goto_last_line(const char* section);

};

}; //namespace pap_common_base

#endif //PAP_COMMON_BASE_INI_H_
