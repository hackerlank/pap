/**
 * PAP Engine ( https://github.com/viticm/pap )
 * $Id share_memory.h
 * @link https://github.com/viticm/pap for the canonical source repository
 * @copyright Copyright (c) 2013-2013 viticm( viticm@126.com )
 * @license
 * @user viticm<viticm@126.com>
 * @date 2013-12-3 11:32:43
 * @uses system share memory model
 */
#ifndef PAP_COMMON_SYS_SHARE_MEMORY_H_
#define PAP_COMMON_SYS_SHARE_MEMORY_H_

#include "server/common/sys/config.h"
#include "server/common/base/log.h"

namespace pap_server_common_sys {

namespace share_memory {

//-- static define
const uint32_t kManagerUnitDataMax = 5000; //如果不需要引入外部，就不要使用宏
const uint8_t kObjMax = 20;
#if defined(__LINUX__)
extern uint32_t lock_times; //内存锁定的时间
extern bool lock_time_enable; //共享内存是否有时间锁的限制
#endif
struct data_header_t {
  uint64_t key;
  uint32_t size;
  uint32_t version;
  data_header_t();
  ~data_header_t();
};

typedef enum {
  kSmptShareMemory,
  kSmptWorld,
  kSmptServer,
} pool_type_enum;

typedef enum {
  kUseFree = 0,
  kUseReadyFree = 1,
  kUseFreed = 2,
  kUseHoldData = 3,
} use_enum; //共享内存的使用状态


typedef enum {
  kFlagFree = 0x00, //共享内存空闲
  kFlagSelfRead = 0x01, //共享内存自己读取
  kFlagSelfWrite = 0x02, //共享内存自己写
  kFlagServerRead = 0x03, //游戏服务器读
  kFlagServerWrite = 0x04, //游戏服务器写
  kFlagWorldRead = 0x05, //世界服务器读
  kFlagWorldWrite = 0x06, //世界服务器写
} flag_enum;

//static define --

namespace api {

#if defined(__LINUX__)
int32_t create(uint64_t key, uint32_t size);
int32_t open(uint64_t key, uint32_t size);
void close(int32_t handle);
char* map(int32_t handle);
#elif defined(__WINDOWS__)
HANDLE create(uint64_t key, uint32_t size);
HANDLE open(uint64_t key, uint32_t size);
void close(HANDLE handle);
char* map(HANDLE handle);
#endif
void unmap(char* pointer);

}; //namespace api

class Base {

 public:
   int32_t cmd_model_; //命令行模式，几种模式在config.h定义
   Base();
   ~Base();

 public:
   bool create(uint64_t key, uint32_t size);
   void destory();
   bool attach(uint64_t key, uint32_t size);
   char* get_data_pointer();
   char* get_data(uint32_t size, uint32_t index);
   uint32_t get_size();
   bool dump(const char* filename);
   bool merge_from_file(const char* filename);
   void set_head_version(uint32_t version);
   uint32_t get_head_version();
 private:
   uint32_t size_;
   char* data_pointer_;
   char* header_;
#if defined(__LINUX__)
   int32_t handle_;
#elif defined(__WINDOWS__)
   HANDLE handle_;
#endif
  
};

template <typename T> //template class must be in one file
class UnitManager {
 
 public:
   T* data_[kManagerUnitDataMax];
   int32_t count_;

 public:
   UnitManager() {
     __ENTER_FUNCTION
       count_ = 0;
       memset(data_, 0, sizeof(T*) * kManagerUnitDataMax);
     __LEAVE_FUNCTION
   };
   ~UnitManager() {
     //do nothing
   };
   void init() {
     __ENTER_FUNCTION
       count_ = 0;
     __LEAVE_FUNCTION
   };
   bool heartbeat(uint32_t time = 0);
   bool add_data(T* data) {
     __ENTER_FUNCTION
       Assert(count_ < kManagerUnitDataMax);
       if (count_ >= kManagerUnitDataMax) return false;
       data_[count_] = data;
       ++count_;
       data_->set_id(count_);
       return true;
     __LEAVE_FUNCTION
       return false;
   };
   bool delete_data(T* data) {
     __ENTER_FUNCTION
       uint32_t id = data->get_id();
       Assert(id < static_cast<uint32_t>(count_));
       if (id >= static_cast<uint32_t>(count_)) return false;
       data_[id] = data_[count_ - 1];
       data->set_id(ID_INVALID);
       --count_;
     __LEAVE_FUNCTION
       return false;
   };
   T* get_data(uint16_t id) {
     __ENTER_FUNCTION
       Assert(id < static_cast<uint32_t>(count_));
       if (id >= static_cast<uint32_t>(count_)) return false;
       return data_[id];
     __LEAVE_FUNCTION
       return false;
   };

};

template<typename T> //模板类只能定义在一个文件内
class UnitPool {

 public:
   UnitPool() {
     __ENTER_FUNCTION
       obj_ = NULL;
       ref_obj_pointer_ = NULL;
       max_size_ = 0;
       position_ = -1;
     __LEAVE_FUNCTION
   };
   ~UnitPool() {
     __ENTER_FUNCTION
       SAFE_DELETE(ref_obj_pointer_);
       SAFE_DELETE_ARRAY(obj_);
     __LEAVE_FUNCTION
   };
   bool init(uint32_t max_count, uint64_t key, pool_type_enum pool_type) {
     __ENTER_FUNCTION
       ref_obj_pointer_ = new Base();
       Assert(ref_obj_pointer_);
       if (!ref_obj_pointer_) return false;
       ref_obj_pointer_->cmd_model_ = g_cmd_model;
       bool result = true;
       result = ref_obj_pointer_->attach(
           key, 
           sizeof(T) * max_count + sizeof(data_header_t));
       if (kSmptShareMemory == pool_type && !result) {
         result = ref_obj_pointer_->create(
             key, 
             sizeof(T) * max_count + sizeof(data_header_t));
       }
       else if(!result) {
         return false;
       }

       if (!result && kCmdModelClearAll == ref_obj_pointer_->cmd_model_) {
         return true;
       }
       else if(!result) {
         pap_server_common_base::Log::save_log(
             "sharememory", 
             "[sharememory][datapool](init) failed");
         Assert(result);
         return result;
       }
       max_size_ = max_count;
       position_ = 0;
       obj_ = new T*[max_size_];
       uint32_t i;
       for (i = 0; i < max_size_; ++i) {
         obj_[i] = reinterpret_cast<T*>
                   (ref_obj_pointer_->get_data(sizeof(T), i));
         if (NULL == obj_[i]) {
           Assert(false);
           return false;
         }
       }
       key_ = key;
       return true;
     __LEAVE_FUNCTION
       return false;
   };
   bool release() {
     __ENTER_FUNCTION
       Assert(ref_obj_pointer_);
       ref_obj_pointer_->destory();
       return true;
     __LEAVE_FUNCTION
       return false;
   };
   T* new_obj() {
     __ENTER_FUNCTION
       Assert(position_ < max_size_);
       if (position_ >= max_size_) return NULL;
       T* obj = obj_[position_];
       obj->set_pool_id(static_cast<uint32_t>(position_)); //this function 
                                                           //must define in T*
       ++position_;
       return obj;
     __LEAVE_FUNCTION
       return NULL;
   };
   void delete_obj(T* obj) {
     __ENTER_FUNCTION
       Assert(obj != NULL);
       Assert(position_ > 0);
       if (NULL == obj || position_ <= 0) return;
       uint32_t delete_index = obj->get_pool_id(); //this function 
                                                   //must define in T*
       Assert(delete_index < position_);
       if (delete_index >= position_) return;
       --position_;
       T* _delete_obj = obj_[delete_index];
       obj_[delete_index] = obj_[position_];
       obj_[position_] = _delete_obj;
       obj_[delete_index]->set_pool_id(delete_index);
       obj_[position_]->set_pool_id(ID_INVALID);
     __LEAVE_FUNCTION
   };
   T* get_obj(int32_t index) {
     __ENTER_FUNCTION
       Assert(index >= 0 && static_cast<uint32_t>(index) < max_size_);
       return obj_[index];
     __LEAVE_FUNCTION
       return NULL;
   };
   uint32_t get_max_size() {
     __ENTER_FUNCTION
       return max_size_;
     __LEAVE_FUNCTION
       return 0;
   };
   int32_t get_position() {
     __ENTER_FUNCTION
       return position_;
     __LEAVE_FUNCTION
       return -1;
   };
   uint64_t get_key() {
     __ENTER_FUNCTION
       return key_;
     __LEAVE_FUNCTION
       return 0;
   };
   bool dump(const char* filename) {
     __ENTER_FUNCTION
       Assert(ref_obj_pointer_);
       if (!ref_obj_pointer_) return false;
       return ref_obj_pointer_->dump(filename);
     __LEAVE_FUNCTION
       return false;
   };
   bool merge_from_file(const char* filename) {
     __ENTER_FUNCTION
       Assert(ref_obj_pointer_);
       if (!ref_obj_pointer_) return false;
       ref_obj_pointer_->merge_from_file(filename);
     __LEAVE_FUNCTION
       return false;
   };
   uint32_t get_head_version() {
     __ENTER_FUNCTION
       Assert(ref_obj_pointer_);
       if (!ref_obj_pointer_) return false;
       ref_obj_pointer_->get_head_version();
     __LEAVE_FUNCTION
       return 0;
   };
   void set_head_version(uint32_t version) {
     __ENTER_FUNCTION
       Assert(ref_obj_pointer_);
       if (!ref_obj_pointer_) return;
       ref_obj_pointer_->set_head_version(version);
     __LEAVE_FUNCTION
   };

 private:
   T** obj_;
   uint32_t max_size_;
   int32_t position_;
   Base* ref_obj_pointer_;
   uint64_t key_;

};

void lock(char &flag, char type);
void unlock(char &flag, char type);
bool trylock(char &flag, char type);

}; //namespace share_memory

}; //namespace pap_server_common_sys

#endif //PAP_COMMON_SYS_SHARE_MEMORY_H_
