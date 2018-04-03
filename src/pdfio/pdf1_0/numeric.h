#pragma once

namespace pdfio
{
	
namespace pdf1_0
{
	
/*! \brief PDF numeric object.*/
template <typename T> class Numeric
{
public:
  /*! \brief Constructor. Initializes the value_ by the value.*/
  Numeric(T value = T())
  : value_(value)
  {
    
  }
  /*! \brief Converts the Numeric to T by returning the value_.*/
  operator T() const
  {
    return value_;
  }
  /*! \brief Converts the Numeric to T by returning the value_.*/
  operator T()
  {
    return value_;
  }
  /*! \brief Assigns the value to the value_.*/
  Numeric &operator=(T value)
  {
    value_ = value;
    return *this;
  }
  
private:
  T value_;
};

} //namespace pdf1_0

} //namespace pdfio