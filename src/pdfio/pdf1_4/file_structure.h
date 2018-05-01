#pragma once

#include "pdfio/pdf1_0/file_structure.h"
#include "array.h"
#include "hexstring.h"

namespace pdfio
{
   
namespace pdf1_4
{
   
/*! \brief PDF File Structure.*/
struct FileStructure
{
public:
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
};
   
}
   
}
