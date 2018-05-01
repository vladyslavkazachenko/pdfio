#pragma once

#include <string>

#include "pdfio/pdf1_0/file_structure.h"
#include "array.h"
#include "hexstring.h"
#include "integer.h"

namespace pdfio
{
   
namespace pdf1_4
{
   
struct FileVersion
{
   /*! \brief PDF File Header.*/
   typedef struct Header
   {
      std::string data_;
      
      static const std::string kVersion1_0;
      static const std::string kVersion1_1;
      static const std::string kVersion1_2;
      static const std::string kVersion1_3;
      static const std::string kVersion1_4;
   } Header;
   
   /*! \brief PDF File Cross-Reference Subsection Entry.*/
   struct XrefEntry
   {
      Integer offset_ = 0;
      Integer generation_ = 0;
      bool inUseFlag_ = true;
   };
   
   /*! \brief PDF File Cross-Reference Subsection.*/
   typedef pdf1_0::FileStructure::XrefSubsection XrefSubsection;
   
   /*! \brief PDF File Cross-Reference Section.*/
   typedef pdf1_0::FileStructure::XrefSection XrefSection;
   
   /*! \brief PDF File Trailer.*/
   class Trailer : public pdf1_0::FileStructure::Trailer
   {
   public:
      /*! \brief Assigns the other to the Trailer.*/
      //Trailer &operator=(const Trailer &other);
      /*! \brief Checks whether parent Dictionary contains entry with key 
       * "Encrypt".
       */
      bool hasEncrypt() const;
      /*! \brief Checks whether parent Dictionary contains entry with key "ID".
       */
      bool hasId() const;
      /*! \brief Returns value by key "ID".*/
      const Array<HexString> &id() const;
      /*! \brief Returns value by key "ID".*/
      Array<HexString> &id();
      /*! \brief Adds optional entries into the parent Dictionary.*/
      void prepare4Reading();
   };
   
   XrefSection xrefSection_;
   Trailer trailer_;
   
};
   
}
   
}
