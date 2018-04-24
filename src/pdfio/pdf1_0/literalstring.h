#pragma once

#include <string>

namespace pdfio
{

namespace pdf1_0
{
/*! \brief PDF Literal String Object.*/
class LiteralString
{
public:
   /*! \brief Converts the LiteralString to std::string by returning the value_.
    */
   inline operator std::string() const
   {
      return value_;
   }
   /*! \brief Converts the LiteralString to std::string by returning the value_.
    */
   inline operator std::string()
   {
      return value_;
   }
   /*! \brief Compares the LiteralString to the value.*/
   inline bool operator==(const std::string &value) const
   {
      return value_ == value;
   }
   /*! \brief Assigns the value to the LiteralString.*/
   inline LiteralString &operator=(const std::string &value)
   {
      value_ = value;
      return *this;
   }
   
private:
   std::string value_;
};
   
} // namespace pdf1_0

} // namespace pdfio
