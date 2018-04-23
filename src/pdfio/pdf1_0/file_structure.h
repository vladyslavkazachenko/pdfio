#pragma once

#include <vector>

#include "integer.h"
#include "dictionary.h"
#include "indirect_reference.h"

namespace pdfio
{
   
namespace pdf1_0
{
   
/*! \brief PDF File Structure.*/
struct FileStructure
{
   /*! \brief PDF File Cross-Reference Subsection Entry.*/
   struct XrefEntry
   {
      Integer offset_ = 0;
      Integer generation_ = 0;
      bool inUseFlag_ = true;
   };
   /*! \brief PDF File Cross-Reference Subsection.*/
   struct XrefSubsection
   {
      Integer firstObjectNumber_ = 0;
      std::vector<XrefEntry> entries_;
   };
   /*! \brief PDF File Cross-Reference Section.*/
   class XrefSection
   {
   public:
      inline const std::vector<XrefSubsection> &subsections() const
      {
         return subsections_;
      }
      inline bool add(const XrefSubsection &subsection)
      {
         subsections_.push_back(subsection);
         return true;
      }
      
   private:
      std::vector<XrefSubsection> subsections_;
   };
   
   /*! \brief PDF File Trailer.*/
   class Trailer : public virtual Dictionary
   {
   public:
      /*! \brief Constructs the Trailer by adding Integer value with key
       *"Size" into the parent Dictionary.*/
      Trailer();
      
      Trailer &operator=(const Trailer &other);
      /*! \brief Returns value by key "Size".*/
      const Integer &size() const;
      /*! \brief Returns value by key "Size".*/
      Integer &size();
      /*! \brief Checks whether parent Dictionary contains entry with 
       * key "Prev".
       */
      bool hasPrev() const;
      /*! \brief Returns value by key "Prev".*/
      const Integer &prev() const;
      /*! \brief Returns value by key "Prev".*/
      Integer &prev();
      /*! \brief Checks whether parent Dictionary contains entry with 
       * key "Root".
       */
      bool hasRoot() const;
      /*! \brief Returns value by key "Root".*/
      const IndirectReference &root() const;
      /*! \brief Returns value by key "Root".*/
      IndirectReference &root();
      /*! \brief Checks whether parent Dictionary contains entry with 
       * key "Info".
       */
      bool hasInfo() const;
      /*! \brief Returns value by key "Info".*/
      const IndirectReference &info() const;
      /*! \brief Returns value by key "Info".*/
      IndirectReference &info();
      /*! \brief Adds optional entries into the parent Dictionary.*/
      void prepare4Reading();
   };
   
   struct Version
   {
      XrefSection xrefSection_;
      Trailer trailer_;
   };

   std::vector<Version> versions_;
};
   
}

}
