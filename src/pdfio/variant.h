#pragma once

#include <memory>
#include <cassert>

namespace pdfio
{
   
class Variant
{
public:
   inline int type() const
   {
      if(value_)
      {
         return value_->type_;
      }
      return KNull;
   }
   template <typename T> T &get() 
   {
      if(!value_ || value_->type_ != GetTypeId<T>())
      {
         set(T());
      }
      return std::static_pointer_cast<ValueAdaptor<T>>(value_)->value_;
   }
   template <typename T> void set(const T &value)
   {
      value_ = std::static_pointer_cast<Value>(
         std::make_shared<ValueAdaptor<T>>(value));
   }
   
   static const int KNull = -1;
   template <typename T> static int GetTypeId();
   
private:
   struct Value
   {
      Value(int type)
      : type_(type)
      {
         
      }
      virtual ~Value() = default;
      
      const int type_;
   };
   
   template <typename T> struct ValueAdaptor: Value
   {
      ValueAdaptor(const T &value)
      : Value(Variant::GetTypeId<T>())
      , value_(value)
      {
         
      }
      
      T value_;
   };
   
   std::shared_ptr<Value> value_;
};
   
}
