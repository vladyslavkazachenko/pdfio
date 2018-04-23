#pragma once

#include <string>

#include "integer.h"
#include "dictionary.h"
#include "array.h"
#include "hexstring.h"
#include "indirect_reference.h"

namespace pdfio
{

namespace pdf1_0
{

/*! \brief PDF stream object.*/
class Stream: public virtual Dictionary
{
public:
   struct Filter
   {
      Name name_;
   };
   /*! \brief Constructs the stream initializing base std::istream and base dictionary.*/
   Stream();
   /*! \brief Returns value by key "Length".*/
   const Integer &length() const;
   /*! \brief Returns value by key "Length".*/
   Integer &length();
   /*! \brief Checks whether the parent Dictionary contains entry with key "DecodeParms".*/
   bool hasDecodeParms() const;
   /*! \brief Returns value by key "DecodeParms".*/
   const Dictionary &decodeParms() const;
   /*! \brief Returns value by key "DecodeParms".*/
   Dictionary &decodeParms();
   /*! \brief Checks whether the parent Dictionary contains entry with key "Filter".*/
   bool hasFilter() const;
   /*! \brief Returns value by key "Filter".*/
   const Filter &filter() const;
   /*! \brief Returns value by key "Filter".*/
   Filter &filter();
   /*! \brief Returns the Stream's data between "stream" and "endstream".*/
   const std::string &data() const;
   /*! \brief Returns the Stream's data between "stream" and "endstream".*/
   std::string &data();
   /*! \brief Inserts optianal entries to the parent Dictionary.*/
   void prepare4Reading();
   
   static const Name kKeyLength;
   static const Name kKeyDecodeParms;
   static const Name kKeyFilter;
   static const Name kKeyColumns;
   static const Name kKeyPredictor;
   
private:
   std::string data_;
};

}

}
